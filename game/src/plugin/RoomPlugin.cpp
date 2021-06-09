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
        // Start a server on port 8080 and start listening
        server = net->add_server(8080);
        server->listen();
    }
}

void update_room(World& wld)
{
    std::optional<Packet> p;
    if (!server)
        return;
    server->clients().performSafeThreadAction(
        [&](std::vector<std::shared_ptr<NetClient>> vec) {
            for (auto& client : vec) {
                p = client->recv();
                if (p && p.value().get_data()) {
                    auto data = p.value().get_data().value();
                    auto str_data = std::string(data.begin(), data.end());

                    std::cout << str_data << std::endl;

                    // We echo back
                    client->send(p.value());
                }
            }
        });
}

void RoomPlugin::plug(App::Builder& builder) const
{
    builder.add_startup_system(System(init_room));
    builder.add_system(System(update_room));
}
