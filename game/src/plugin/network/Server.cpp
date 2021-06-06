#include "plugin/network/NetworkManager.hpp"
#include <string>

NetworkManager::Server::Server(const NetworkId& id, int port)
    : m_id(id)
{
    NetworkId client_id = NetworkId::generate();

    m_clients.emplace(client_id, Client { client_id, "", 0 });
}

NetworkManager::Server::Server(int port)
    : m_id(NetworkId::generate())
{
}

NetworkId NetworkManager::Server::id() const
{
    return m_id;
}

void NetworkManager::Server::start_listenning()
{
}

void NetworkManager::Server::stop_listenning()
{
}

std::vector<IClient*> NetworkManager::Server::clients()
{
    std::vector<IClient*> res;

    for (auto& pair : m_clients) {
        res.push_back(&pair.second);
    }
    return res;
}

IClient* NetworkManager::Server::client(const NetworkId& id)
{
    auto client = m_clients.find(id);

    if (client == m_clients.end()) {
        return nullptr;
    }
    return &client->second;
}

void NetworkManager::Server::disconnect_client(const NetworkId& id)
{
}

void NetworkManager::Server::disconnect_clients()
{
}

void NetworkManager::Server::send(const Packet& packet)
{
    for (auto& client : m_clients) {
        client.second.send(packet);
    }
}

void NetworkManager::Server::update()
{
    for (auto& client : m_clients) {
        client.second.update();
    }
}
