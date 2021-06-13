/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Client
*/

#include "plugin/network/Client.hpp"
#include "plugin/network/NetworkManager.hpp"
#include "plugin/network/Utils.hpp"

#include <string>
#include <thread>

Client::Client(const std::string& ip, unsigned short port, const NetworkId& id)
    : m_id(id)
{
    m_tcp_client.connect(ip, port);
    m_udp_client.set_destination(ip, port);
    m_udp_send_thread = std::thread(&Client::net_udp_thread_send_logic, this);
    m_udp_read_thread = std::thread(&Client::net_udp_thread_recv_logic, this);
    m_tcp_send_thread = std::thread(&Client::net_tcp_thread_send_logic, this);
    m_tcp_read_thread = std::thread(&Client::net_tcp_thread_recv_logic, this);
}

Client::~Client()
{
    m_tcp_ready = false;
    m_udp_ready = false;
    m_tcp_client.close();
    m_udp_client.close();
    m_sync_buffer.outgoing_hp_sync_ringer.ring();
    m_sync_buffer.outgoing_lp_sync_ringer.ring();
    m_udp_send_thread.join();
    m_tcp_send_thread.join();
    m_udp_read_thread.join();
    m_tcp_read_thread.join();
}

NetworkId Client::id() const
{
    return m_id;
}

void Client::send(const Packet& packet)
{
    if (packet.is_important()) {
        m_sync_buffer.outgoing_packets_hp.push(packet);
        m_sync_buffer.outgoing_hp_sync_ringer.ring();
    } else {
        m_sync_buffer.outgoing_packets_lp.push(packet);
        m_sync_buffer.outgoing_lp_sync_ringer.ring();
    }
}

std::optional<Packet> Client::recv()
{
    return m_sync_buffer.incoming_packets.pop();
}

void Client::net_tcp_thread_send_logic()
{
    try {
        while (m_tcp_ready) {
            m_sync_buffer.outgoing_hp_sync_ringer.waitForOrder();
            if (!m_tcp_ready)
                break;
            auto opacket = m_sync_buffer.outgoing_packets_hp.pop();

            if (opacket) {
                // Send packet size as an unsigned int
                m_tcp_client.send(Utils::get_bytes(
                    (unsigned int)(opacket.value().get_data()->size())));

                // Send actual packet size
                m_tcp_client.send(opacket.value().get_data().value());
            }
        }
    } catch (const std::exception& e) {
        m_tcp_ready = false;
    }
}

void Client::net_tcp_thread_recv_logic()
{
    try {
        while (m_tcp_ready) {
            auto len_data = m_tcp_client.recv(4);
            if (!m_tcp_ready)
                break;
            unsigned int psize = Utils::get<unsigned int>(len_data);
            auto data = m_tcp_client.recv(psize);
            Packet p;

            p.set_data(data);
            m_sync_buffer.incoming_packets.push(p);
        }
    } catch (const std::exception& e) {
        m_tcp_ready = false;
    }
}

void Client::net_udp_thread_send_logic()
{
    try {
        while (m_udp_ready) {
            m_sync_buffer.outgoing_lp_sync_ringer.waitForOrder();
            if (!m_udp_ready)
                break;
            auto opacket = m_sync_buffer.outgoing_packets_lp.pop();

            if (opacket) {
                // Todo pad or cut packet to match UDP agreed size
                m_udp_client.send(opacket.value().get_data().value());
            }
        }
    } catch (const std::exception& e) {
        m_udp_ready = false;
    }
}

void Client::net_udp_thread_recv_logic()
{
    try {
        while (m_udp_ready) {
            auto data = m_tcp_client.recv(2048);
            Packet p;

            p.set_data(data);
            m_sync_buffer.incoming_packets.push(p);
        }
    } catch (const std::exception& e) {
        m_tcp_ready = false;
    }
}
