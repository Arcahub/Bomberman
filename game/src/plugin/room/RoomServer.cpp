#include "plugin/room/RoomServer.hpp"
#include "Player.hpp"
#include "ige.hpp"

using ige::ecs::World;

RoomServer::RoomServer(World& wld, int port)
{
    auto net = wld.get<NetworkManager>();

    if (!net) {
        return;
    }

    m_server = net->add_server(port);
}

void RoomServer::send_room_data(const std::deque<uint8_t>& data)
{
    RoomPacket packet;

    packet.type = RoomPacketType::ROOM;
    packet.set_data(data);
    m_server->send(packet);
}

void RoomServer::send_player_data(
    const RoomLocalPlayer& player, const std::deque<uint8_t>& data)
{
    RoomPacket packet;

    if (!player.network_id) {
        return;
    }

    packet.type = RoomPacketType::PLAYER;
    packet.netword_id = player.network_id;
    packet.set_data(data);
    m_server->send(packet);
}

std::optional<std::deque<uint8_t>> RoomServer::recv_room_data()
{
    if (m_room_packets.size() == 0) {
        return {};
    }

    RoomPacket packet = m_room_packets.front();

    m_room_packets.pop();
    return packet.get_data();
}

std::optional<std::deque<uint8_t>>
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
    for (auto& client : m_server->clients()) {
        RoomPacket packet;
        while (client->recv(packet)) {
            if (packet.type == RoomPacketType::ROOM) {
                m_room_packets.push(packet);
            } else if (packet.netword_id) {
                m_players_packets[*packet.netword_id].push(packet);
            }
            packet.reset();
        }
    }
}
