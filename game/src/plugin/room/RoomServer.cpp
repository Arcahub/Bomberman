#include "plugin/room/RoomServer.hpp"
#include "ige.hpp"

using ige::ecs::World;

RoomServer::RoomServer(World& wld, int port)
{
    auto net = wld.get<NetworkManager>();

    if (!net) {
        return;
    }

    m_server = net->add_server(port);
    m_server->listen();
}

void RoomServer::send_room_data(const std::vector<char>& data)
{
    RoomPacket packet;

    packet.type = RoomPacketType::ROOM;
    packet.set_data(data);
    m_server->clients().performSafeThreadAction([&](auto& clients) {
        for (auto& client : clients) {
            Packet p;
            p.set_data(packet.serialize());
            client->send(p);
        }
    });
    // m_server->send(packet.get_data());
}

void RoomServer::send_player_data(
    const RoomLocalPlayer& player, const std::vector<char>& data)
{
    RoomPacket packet;

    if (!player.network_id) {
        return;
    }

    packet.type = RoomPacketType::PLAYER;
    packet.netword_id = player.network_id;
    packet.set_data(data);
    m_server->clients().performSafeThreadAction([&](auto& clients) {
        for (auto& client : clients) {
            Packet p;
            p.set_data(packet.serialize());
            client->send(p);
        }
    });
}

std::optional<std::vector<char>> RoomServer::recv_room_data()
{
    if (m_room_packets.size() == 0) {
        return {};
    }

    RoomPacket packet = m_room_packets.front();

    m_room_packets.pop();
    return packet.get_data();
}

std::optional<std::vector<char>>
RoomServer::recv_player_data(const RoomNetworkPlayer& player)
{
    if (m_players_packets.find(player.network_id) == m_players_packets.end()) {
        return {};
    }

    if (m_players_packets[player.network_id].size() == 0) {
        return {};
    }
    RoomPacket packet = m_players_packets[player.network_id].front();

    m_players_packets[player.network_id].pop();
    return packet.get_data();
}

void RoomServer::update(World& wld)
{
    m_server->clients().performSafeThreadAction([&](auto& clients) {
        for (auto& client : clients) {
            while (std::optional<Packet> p = client->recv()) {
                RoomPacket packet;
                packet.deserialize(p->get_data());
                if (packet.type == RoomPacketType::ROOM) {
                    m_room_packets.push(packet);
                } else if (packet.type == RoomPacketType::PLAYER) {
                    m_players_packets[*packet.netword_id].push(packet);
                }
            }
        }
    });
}
