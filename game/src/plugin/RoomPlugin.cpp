#include "plugin/RoomPlugin.hpp"
#include "plugin/NetworkPlugin.hpp"
#include "plugin/network/Server.hpp"
#include <iostream>
#include <string>

using ige::core::App;
using ige::ecs::System;
using ige::ecs::World;

Server* server = nullptr;

void init_room(World& wld)
{
    auto net = wld.get<NetworkManager>();

    if (net) {
        server = net->add_server();
    }
}

void update_room(World& wld)
{
    if (!server)
        return;
}

void RoomPlugin::plug(App::Builder& builder) const
{
    builder.add_startup_system(System(init_room));
    builder.add_system(System(update_room));
}
