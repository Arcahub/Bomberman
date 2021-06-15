#include "plugin/network/NetClient.hpp"
#include "plugin/network/NetworkManager.hpp"
#include "plugin/network/NetworkUtils.hpp"
#include <string>

NetClient::NetClient(const NetworkId& id, inl::core::TcpClient tcp)
    : m_id(id)
    , m_tcp_client(std::move(tcp))
{
    m_udp_send_thread
        = std::thread(&NetClient::net_udp_thread_send_logic, this);
    m_tcp_send_thread
        = std::thread(&NetClient::net_tcp_thread_send_logic, this);
    m_tcp_read_thread
        = std::thread(&NetClient::net_tcp_thread_recv_logic, this);
}

NetClient::NetClient(inl::core::TcpClient tcp)
    : NetClient::NetClient(NetworkId::generate(), std::move(tcp))
{
}

NetClient::~NetClient()
{
    m_tcp_ready = false;
    m_udp_ready = false;
    m_tcp_client.close();
    m_udp_client.close();
    m_sync_buffer.outgoing_hp_sync_ringer.ring();
    m_sync_buffer.outgoing_lp_sync_ringer.ring();
    m_tcp_read_thread.join();
    m_tcp_send_thread.join();
    m_udp_send_thread.join();
}

NetworkId NetClient::id() const
{
    return m_id;
}

void NetClient::send(const Packet& packet)
{
    if (packet.is_important()) {
        m_sync_buffer.outgoing_packets_hp.push(packet);
        m_sync_buffer.outgoing_hp_sync_ringer.ring();
    } else {
        m_sync_buffer.outgoing_packets_lp.push(packet);
        m_sync_buffer.outgoing_lp_sync_ringer.ring();
    }
}

std::optional<Packet> NetClient::recv()
{
    return m_sync_buffer.incoming_packets.pop();
}

void NetClient::net_tcp_thread_send_logic()
{
    try {
        while (m_tcp_ready) {
            m_sync_buffer.outgoing_hp_sync_ringer.waitForOrder();
            auto opacket = m_sync_buffer.outgoing_packets_hp.pop();

            if (opacket) {
                // Send packet size as an unsigned int
                m_tcp_client.send(NetworkUtils::get_bytes(
                    (unsigned int)(opacket.value().get_data().size())));

                // Send actual packet size
                m_tcp_client.send(opacket.value().get_data());
            }
        }
    } catch (const std::exception& e) {
        m_tcp_ready = false;
    }
}

void NetClient::net_tcp_thread_recv_logic()
{
    try {
        while (m_tcp_ready) {
            auto len_data = m_tcp_client.recv(4);
            if (!m_tcp_ready)
                break;
            unsigned int psize = NetworkUtils::get<unsigned int>(len_data);
            auto data = m_tcp_client.recv(psize);
            Packet p;

            p.set_data(data);
            m_sync_buffer.incoming_packets.push(p);
        }
    } catch (const std::exception& e) {
        m_tcp_ready = false;
    }
}

void NetClient::net_udp_thread_send_logic()
{
    try {
        while (m_udp_ready) {
            m_sync_buffer.outgoing_lp_sync_ringer.waitForOrder();
            auto opacket = m_sync_buffer.outgoing_packets_lp.pop();

            if (opacket) {
                m_udp_client.send(opacket.value().get_data());
            }
        }
    } catch (const std::exception& e) {
        m_udp_ready = false;
    }
}

bool NetClient::is_connected() const
{
    return m_tcp_ready;
}
