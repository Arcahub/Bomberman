#include "plugin/room/RoomClient.hpp"
#include "ige.hpp"
#include "scripts/NetworkController.hpp"

using ige::ecs::World;
using ige::plugin::input::InputManager;
using ige::plugin::input::InputRegistryState;
using ige::plugin::input::KeyboardKey;
using ige::plugin::script::Scripts;

RoomClient::RoomClient(const std::string& addr, int port)
{
}

void RoomClient::send_room_data(const std::vector<char>& data)
{
    RoomPacket packet;

    packet.type = RoomPacketType::ROOM;
    packet.set_data(data);
    // m_client->send(packet);
}

void RoomClient::send_player_data(
    const RoomPlayer& player, const std::vector<char>& data)
{
    RoomPacket packet;

    packet.type = RoomPacketType::PLAYER;
    packet.player_id = player.id;
    packet.set_data(data);
    // m_client->send(packet);
}

std::optional<RoomPacket> RoomClient::recv()
{
    if (m_room_packets.size() == 0) {
        return {};
    }

    RoomPacket packet = m_room_packets.front();

    m_room_packets.pop();
    return packet;
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
