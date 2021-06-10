#include "plugin/BombermanLobbyPlugin.hpp"
#include "ige.hpp"
#include "plugin/room/RoomClient.hpp"
#include "plugin/room/RoomServer.hpp"

using ige::core::App;
using ige::ecs::System;
using ige::ecs::World;

static void update_client(World& wld)
{
    RoomClient* room = wld.get<RoomClient>();

    if (!room) {
        return;
    }

    while (auto data = room->recv_room_data()) {
        // Handle room packet
    }
    for (auto player : room->players()) {
        if (player->type == RoomPlayerType::NETWORK) {
            while (auto data = room->recv_player_data(
                       std::get<RoomNetworkPlayer>(player->data))) {
                // handle player packet
            }
        } else if (player->type == RoomPlayerType::LOCAL) {
            // set local player input
            std::get<RoomLocalPlayer>(player->data).serialize_inputs(wld);
        }
    }
}

static void update_server(World& wld)
{
    RoomServer* room = wld.get<RoomServer>();

    if (!room) {
        return;
    }

    while (auto data = room->recv_room_data()) {
        // Handle room packet
    }

    for (auto player : room->players()) {
        if (player->type == RoomPlayerType::NETWORK) {
            while (auto data = room->recv_player_data(
                       std::get<RoomNetworkPlayer>(player->data))) {
                // handle player packet
                // broadcast to other player
            }
        } else if (player->type == RoomPlayerType::LOCAL) {
            // send local player input
            auto local_player = std::get<RoomLocalPlayer>(player->data);
            room->send_player_data(
                local_player, local_player.serialize_inputs(wld));
        }
    }
}

void BombermanLobbyPlugin::plug(App::Builder& builder) const
{
    builder.add_system(System(update_client));
    builder.add_system(System(update_server));
}
