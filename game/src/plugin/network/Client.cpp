#include "plugin/network/NetworkManager.hpp"
#include <string>

NetworkManager::Client::Client(
    const NetworkId& id, const std::string& addr, int port)
    : m_id(id)
{
    // launch connection in thread
}

NetworkManager::Client::Client(const std::string& addr, int port)
    : m_id(NetworkId::generate())
{
    // launch connection in thread
}

NetworkId NetworkManager::Client::id() const
{
    return m_id;
}

void NetworkManager::Client::send(const Packet& packet)
{
    auto buff = packet.serialize();

    for (auto& val : buff) {
        m_write_buffer.push_back(val);
    }
}

void NetworkManager::Client::recv(Packet& packet)
{
    size_t read = 0;

    if (packet.deserialize(m_read_buffer, read)) {
        m_read_buffer.erase(
            m_read_buffer.begin(), m_read_buffer.begin() + read);
    }
}

void NetworkManager::Client::update()
{
    // push send packet to thread
    // pull input from thread
    m_read_buffer.clear();
    for (auto& val : m_write_buffer) {
        m_read_buffer.push_back(val);
    }
    m_write_buffer.clear();
}
