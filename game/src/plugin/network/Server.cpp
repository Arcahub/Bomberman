#include "plugin/network/Server.hpp"
#include "concurrent/ConcurrentVector.hpp"
#include "plugin/network/NetClient.hpp"
#include "plugin/network/NetworkManager.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

Server::Server(NetworkId id, int port)
    : m_id(id)
    , m_tcp_listener(port)
{
}

Server::Server(int port)
    : Server::Server(NetworkId::generate(), port)
{
}

Server::Server(Server&& other)
    : m_id(other.m_id)
    , m_tcp_listener(std::move(other.m_tcp_listener))
{
    this->m_listening = (bool)other.m_listening;
}

Server::~Server()
{
    m_listening = false;
    m_clients.clear();
}

NetworkId Server::id() const
{
    return m_id;
}

void Server::listen()
{
    m_tcp_listener.listen();
    m_listening = true;
    m_accept_thread = std::thread(&Server::accept_thread_logic, this);
}

Server& Server::operator=(Server&& other)
{
    this->m_listening = (bool)other.m_listening;
    this->m_tcp_listener = std::move(other.m_tcp_listener);
    return *this;
}

void Server::disconnect_client(const NetworkId& id)
{
}

void Server::broadcast(const Packet& packet)
{
    m_clients.performSafeThreadAction(
        [&](std::vector<std::shared_ptr<NetClient>> clients) {
            for (auto& cli : clients) {
                cli->send(packet);
            }
        });
}

void Server::accept_thread_logic()
{
    try {
        while (m_listening) {
            std::shared_ptr<NetClient> new_client = std::shared_ptr<NetClient>(
                new NetClient(std::move(m_tcp_listener.accept())));

            std::cerr << "Accepted new NetClient." << std::endl;
            m_clients.push_back(std::move(new_client));
        }
    } catch (const std::exception& e) {
        m_listening = false;
    }
}
