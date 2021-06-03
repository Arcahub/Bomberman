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
    m_id = net->add_server(port)->id();
}

void RoomServer::handle_new_player(World& wld, IClient* client)
{

    RoomNetworkPlayer player = {
        Player::generate(wld, {}),
    };
    m_players.push_back({
        RoomPlayerType::NETWORK,
        player,
    });
    RoomPacket packet;
    packet.type = RoomPacketType::ROOM_JOIN;
    client->send(packet);
}

void RoomServer::player_update(World& wld, const RoomPlayer& player)
{
    switch (player.type) {
    case RoomPlayerType::NETWORK:
        /* code */
        break;
    case RoomPlayerType::LOCAL:
        /* code */
        break;
    default:
        break;
    }
}

void RoomServer::update(World& wld)
{
    auto net = wld.get<NetworkManager>();

    if (!net) {
        return;
    }
    auto server = net->server(m_id);

    for (auto client : server->clients()) {
        if (find_player(client->id()) == nullptr) {
            handle_new_player(wld, client);
        }
    }
    auto players = m_players;
    for (auto& player : players) {
        player_update(wld, player);
    }
}
