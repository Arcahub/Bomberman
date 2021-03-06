#include "plugin/RoomPlugin.hpp"
#include "plugin/NetworkPlugin.hpp"
#include "plugin/network/Server.hpp"
#include <string>

using ige::core::App;
using ige::ecs::System;
using ige::ecs::World;

static void update_room_server(World& wld)
{
    auto room = wld.get<RoomServer>();

    if (!room) {
        return;
    }
    room->update();
}

static void update_room_client(World& wld)
{
    auto room = wld.get<RoomClient>();

    if (!room) {
        return;
    }
    room->update();
}

void RoomPlugin::plug(App::Builder& builder) const
{
    builder.add_system(System::from(update_room_server));
    builder.add_system(System::from(update_room_client));
}
