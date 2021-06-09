#include "plugin/network/NetworkManager.hpp"
#include "plugin/network/Server.hpp"

Server* NetworkManager::add_server(int port)
{
    NetworkId id = NetworkId::generate();
    std::shared_ptr<Server> server
        = std::shared_ptr<Server>(new Server(id, port));

    m_servers.emplace(id, server);
    return server.get();
}

Server* NetworkManager::server(const NetworkId& id)
{
    auto server = m_servers.find(id);

    if (server == m_servers.end()) {
        return nullptr;
    }
    return server->second.get();
}

bool NetworkManager::remove_server(const NetworkId& id)
{
    return m_servers.erase(id);
}

void NetworkManager::update()
{
}
