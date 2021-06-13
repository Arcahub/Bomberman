#include "plugin/room/RoomClient.hpp"
#include "ige.hpp"

using ige::ecs::World;
using ige::plugin::input::InputManager;
using ige::plugin::input::InputRegistryState;
using ige::plugin::input::KeyboardKey;
using ige::plugin::script::Scripts;

RoomClient::RoomClient(const std::string& addr, int port)
    : m_client(std::make_unique<Client>(addr, port))
{
}

void RoomClient::send_room_data(const std::vector<char>& data)
{
    RoomPacket packet;

    packet.type = RoomPacketType::ROOM;
    packet.set_data(data);
    Packet p;
    p.set_data(packet.serialize());
    m_client->send(p);
}

void RoomClient::send_player_data(
    const RoomPlayer& player, const std::vector<char>& data)
{
    RoomPacket packet;

    packet.type = RoomPacketType::PLAYER;
    packet.player_id = player.id;
    packet.set_data(data);
    Packet p;
    p.set_data(packet.serialize());
    m_client->send(p);
}

std::optional<RoomPacket> RoomClient::recv()
{
    if (m_packets.size() == 0) {
        return {};
    }

    RoomPacket packet = m_packets.front();

    m_packets.pop();
    return packet;
}

void RoomClient::update()
{
    while (auto p = m_client->recv()) {
        auto packet = RoomPacket::deserialize(p->get_data());
        packet.sender_id = 0;
        m_packets.push(packet);
    }
}
