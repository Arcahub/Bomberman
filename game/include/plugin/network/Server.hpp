#ifndef SERVER_HPP_
#define SERVER_HPP_

#include "NetClient.hpp"
#include "NetworkId.hpp"
#include "Packet.hpp"
#include "SynchroThreadBuffer.hpp"
#include "concurrent/ConcurrentVector.hpp"
#include "inl.hpp"
#include <atomic>
#include <concepts>
#include <deque>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <variant>

class Server {
public:
    Server(NetworkId id, int port = -1);
    Server(int port = -1);
    Server(const Server&) = delete;
    Server(Server&&);
    ~Server();

    NetworkId id() const;

    void listen();

    void broadcast(const Packet& packet);

    void disconnect_client(const NetworkId& id);

    Server& operator=(Server&&);

protected:
private:
    NetworkId m_id;
    ConcurrentVector<std::shared_ptr<NetClient>> m_clients;
    std::thread m_network_thread;
    std::thread m_accept_thread;
    inl::core::TcpListener m_tcp_listener;
    std::atomic<bool> m_listening = false;

    void accept_thread_logic();
};

#endif /* !SERVER_HPP_ */
