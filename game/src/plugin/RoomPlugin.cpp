#include "plugin/RoomPlugin.hpp"
#include "plugin/NetworkPlugin.hpp"
#include <iostream>
#include <string>

using ige::core::App;
using ige::ecs::System;
using ige::ecs::World;

IServer* server = nullptr;

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
    for (auto client : server->clients()) {
        Packet packet;
        std::string test = "Test";
        packet.set_data({ test.begin(), test.end() });
        client->send(packet);
    }
    server->update();
    for (auto client : server->clients()) {

        Packet packet;
        client->recv(packet);
        // std::cout << packet.is_complete() << std::endl;
        if (auto data = packet.get_data()) {
            std::cout << std::string(data->begin(), data->end()) << std::endl;
        }
    }
}

void RoomPlugin::plug(App::Builder& builder) const
{
    builder.add_startup_system(System(init_room));
    builder.add_system(System(update_room));
}
