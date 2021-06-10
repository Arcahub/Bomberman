#include "plugin/network/NetworkManager.hpp"

std::shared_ptr<IServer> NetworkManager::add_server(int port)
{
    NetworkId id = NetworkId::generate();

    return m_servers.emplace(id, std::make_shared<Server>(id, port))
        .first->second;
}

std::shared_ptr<IServer> NetworkManager::server(const NetworkId& id)
{
    auto server = m_servers.find(id);

    if (server == m_servers.end()) {
        return nullptr;
    }
    return server->second;
}

const std::shared_ptr<IServer> NetworkManager::server(const NetworkId& id) const
{
    auto server = m_servers.find(id);

    if (server == m_servers.end()) {
        return nullptr;
    }
    return server->second;
}

bool NetworkManager::remove_server(const NetworkId& id)
{
    return m_servers.erase(id);
}

std::shared_ptr<IClient>
NetworkManager::add_client(const std::string& addr, int port)
{
    NetworkId id = NetworkId::generate();

    return m_clients.emplace(id, std::make_shared<Client>(id, addr, port))
        .first->second;
}

std::shared_ptr<IClient> NetworkManager::client(const NetworkId& id)
{
    auto client = m_clients.find(id);

    if (client == m_clients.end()) {
        return nullptr;
    }
    return client->second;
}

const std::shared_ptr<IClient> NetworkManager::client(const NetworkId& id) const
{
    auto client = m_clients.find(id);

    if (client == m_clients.end()) {
        return nullptr;
    }
    return client->second;
}

bool NetworkManager::remove_client(const NetworkId& id)
{
    return m_clients.erase(id);
}

void NetworkManager::update()
{
    for (auto& client : m_clients) {
        client.second->update();
    }
    for (auto& server : m_servers) {
        server.second->update();
    }
}
