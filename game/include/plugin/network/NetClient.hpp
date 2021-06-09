/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include "NetworkId.hpp"
#include "SynchroThreadBuffer.hpp"
#include "inl.hpp"
#include <thread>

class NetClient {
public:
    NetClient(const NetworkId& id, inl::core::TcpClient tcp_socket);
    NetClient(inl::core::TcpClient tcp_socket);
    ~NetClient();

    NetworkId id() const;

    void send(const Packet& packet);
    void recv(Packet& packet);

protected:
private:
    NetworkId m_id;
    SynchroThreadBuffer m_sync_buffer;
    inl::core::TcpClient m_tcp_client;
    inl::core::UdpClient m_udp_client;

    bool m_tcp_ready = true;
    bool m_udp_ready = true;

    std::thread m_udp_send_thread;
    std::thread m_tcp_send_thread;
    std::thread m_tcp_read_thread;

    void net_tcp_thread_send_logic();
    void net_udp_thread_send_logic();
    void net_tcp_thread_recv_logic();
};

#endif /* !CLIENT_HPP_ */
