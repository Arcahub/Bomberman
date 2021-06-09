#include "plugin/NetworkPlugin.hpp"
#include "ige.hpp"

using ige::core::App;
using ige::ecs::System;
using ige::ecs::World;

static int client = 0;
static int server = 0;
static int server_client = 0;

static void init_network(World& wld)
{
    NetworkManager& nmanager = wld.emplace<NetworkManager>();

    // Start a server on port 8080 and start listening
    nmanager.add_server(8080)->listen();
}

static void update_network_manager(World& wld)
{
    auto net = wld.get<NetworkManager>();

    if (!net)
        return;
    net->update();
}

void NetworkPlugin::plug(App::Builder& builder) const
{
    builder.add_startup_system(System(init_network));
}
