#include "plugin/room/RoomClient.hpp"
#include "Player.hpp"
#include "ige.hpp"
#include "scripts.hpp"

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
    auto client = net->add_client(addr, port);
    m_network_id = client->id();
}

void RoomClient::add_player(World& wld)
{
    RoomLocalPlayer player = { Player::generate(wld, {}) };
    m_players.push_back({ RoomPlayerType::LOCAL, player });
}

void RoomClient::handle_room_join_packet(World& wld, const RoomPacket& packet)
{
}

void RoomClient::handle_player_join_packet(World& wld, const RoomPacket& packet)
{
    Player::generate(wld, {});
}

void RoomClient::update(World& wld)
{
    auto net = wld.get<NetworkManager>();

    if (!net) {
        return;
    }
    auto client = net->client(m_network_id);

    while (1) {
        RoomPacket packet;
        client->recv(packet);
        if (!packet.is_complete()) {
            break;
        }
        switch (packet.type) {
        case RoomPacketType::ROOM_JOIN:
            handle_room_join_packet(wld, packet);
            break;
        case RoomPacketType::ROOM_UPDATE:
            break;
        case RoomPacketType::ROOM_LEAVE:
            /* code */
            break;
        case RoomPacketType::PLAYER_JOIN:
            handle_player_join_packet(wld, packet);
            break;
        case RoomPacketType::PLAYER_UPDATE:
            if (auto player = find_player(packet.netword_id)) {
                player->handle_update_packet(wld, packet);
            }
            break;
        default:
            break;
        }
    }
    for (auto& player : m_players) {
        switch (player.type) {
        case RoomPlayerType::LOCAL:
            std::get<RoomLocalPlayer>(player.data).generate_update_packet(wld);
            break;
        default:
            break;
        }
    }
}
