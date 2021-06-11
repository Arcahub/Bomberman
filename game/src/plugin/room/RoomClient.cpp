#include "plugin/room/RoomClient.hpp"
#include "ige.hpp"
#include "scripts/NetworkController.hpp"

using ige::ecs::World;
using ige::plugin::input::InputManager;
using ige::plugin::input::InputRegistryState;
using ige::plugin::input::KeyboardKey;
using ige::plugin::script::Scripts;

RoomClient::RoomClient(World& wld, const std::string& addr, int port)
{
    auto net = wld.get<NetworkManager>();

    if (!net) {
        return;
    }

    // m_client = net->add_client(addr, port);
}

void RoomClient::send_room_data(const std::vector<char>& data)
{
    RoomPacket packet;

    packet.type = RoomPacketType::ROOM;
    packet.set_data(data);
    // m_client->send(packet);
}

void RoomClient::send_player_data(
    const RoomLocalPlayer& player, const std::vector<char>& data)
{
    RoomPacket packet;

    if (!player.network_id) {
        return;
    }

    packet.type = RoomPacketType::PLAYER;
    packet.netword_id = player.network_id;
    packet.set_data(data);
    // m_client->send(packet);
}

std::optional<std::vector<char>> RoomClient::recv_room_data()
{
    if (m_room_packets.size() == 0) {
        return {};
    }

    RoomPacket packet = m_room_packets.front();

    m_room_packets.pop();
    return packet.get_data();
}

std::optional<std::vector<char>>
RoomClient::recv_player_data(const RoomNetworkPlayer& player)
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

void RoomClient::update(World& wld)
{
    RoomPacket packet;

    // while (m_client->recv(packet)) {
    //     if (packet.type == RoomPacketType::ROOM) {
    //         m_room_packets.push(packet);
    //     } else if (packet.netword_id) {
    //         m_players_packets[*packet.netword_id].push(packet);
    //     }

    //     packet.reset();
    // }
}
