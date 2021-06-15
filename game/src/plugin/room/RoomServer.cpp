#include "plugin/room/RoomServer.hpp"
#include "ige.hpp"

using ige::ecs::World;

RoomServer::RoomServer(int port)
    : m_server(port)
{
    m_server.listen();
}

void RoomServer::send_room_data(const std::vector<char>& data)
{
    RoomPacket packet;

    packet.type = RoomPacketType::ROOM;
    packet.set_data(data);
    Packet p;
    p.set_data(packet.serialize());
    m_server.clients().performSafeThreadAction([&](auto& clients) {
        for (auto& client : clients) {
            client->send(p);
        }
    });
}

void RoomServer::send_room_data(
    const std::vector<char>& data, const RoomPlayer& dest)
{
    RoomPacket packet;

    packet.type = RoomPacketType::ROOM;
    packet.set_data(data);
    Packet p;
    p.set_data(packet.serialize());

    auto pl = m_players_network_id.find(dest.id);
    if (pl != m_players_network_id.end()) {
        auto network_id = pl->second;

        m_server.clients().performSafeThreadAction([&](auto& clients) {
            for (auto& client : clients) {
                if (client->id() == network_id) {
                    client->send(p);
                }
            }
        });
    }
}

void RoomServer::send_room_data(
    const std::vector<char>& data, const NetworkId& dest)
{
    RoomPacket packet;

    packet.type = RoomPacketType::ROOM;
    packet.set_data(data);
    Packet p;
    p.set_data(packet.serialize());

    int counter = 0;

    m_server.clients().performSafeThreadAction([&](auto& clients) {
        for (auto& client : clients) {
            if (client->id() == dest) {
                client->send(p);
                counter++;
            }
        }
    });
}

void RoomServer::send_player_data(
    const RoomPlayer& player, const std::vector<char>& data)
{
    RoomPacket packet;

    if (!m_server.clients().size() == 0) {
        return;
    }

    packet.type = RoomPacketType::PLAYER;
    packet.player_id = player.id;
    packet.set_data(data);
    Packet p;
    p.set_data(packet.serialize());
    m_server.clients().performSafeThreadAction([&](auto& clients) {
        for (auto& client : clients) {
            client->send(p);
        }
    });
}

void RoomServer::send_player_data(
    const RoomPlayer& player, const std::vector<char>& data,
    const RoomPlayer& dest)
{
    RoomPacket packet;

    if (m_server.clients().size() == 0) {
        return;
    }

    packet.type = RoomPacketType::PLAYER;
    packet.player_id = player.id;
    packet.set_data(data);
    Packet p;
    p.set_data(packet.serialize());

    auto pl = m_players_network_id.find(dest.id);
    if (pl != m_players_network_id.end()) {
        auto network_id = pl->second;

        m_server.clients().performSafeThreadAction([&](auto& clients) {
            for (auto& client : clients) {
                if (client->id() == network_id) {
                    client->send(p);
                }
            }
        });
    }
}

void RoomServer::send_player_data(
    const RoomPlayer& player, const std::vector<char>& data,
    const NetworkId& dest)
{
    RoomPacket packet;

    if (!m_server.clients().size() == 0) {
        return;
    }

    packet.type = RoomPacketType::PLAYER;
    packet.player_id = player.id;
    packet.set_data(data);
    Packet p;
    p.set_data(packet.serialize());

    m_server.clients().performSafeThreadAction([&](auto& clients) {
        for (auto& client : clients) {
            if (client->id() == dest) {
                client->send(p);
            }
        }
    });
}

std::optional<RoomPacket> RoomServer::recv()
{
    if (m_packets.size() == 0) {
        return {};
    }

    RoomPacket packet = m_packets.front();

    m_packets.pop();
    return packet;
}

void RoomServer::update()
{
    m_server.clients().performSafeThreadAction([&](auto& clients) {
        for (auto& client : clients) {
            while (std::optional<Packet> p = client->recv()) {

                RoomPacket packet = RoomPacket::deserialize(p->get_data());
                packet.sender_id = client->id();
                if (packet.type == RoomPacketType::PLAYER) {
                    std::cout << "[NetServer] New client joined"
                              << packet.sender_id.value() << std::endl;
                    m_players_network_id[*packet.player_id] = client->id();
                }
                m_packets.push(packet);
            }
        }
    });
}
