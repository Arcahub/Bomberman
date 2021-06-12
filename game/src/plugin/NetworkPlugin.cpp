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
}

void NetworkPlugin::plug(App::Builder& builder) const
{
    builder.add_startup_system(System::from(init_network));
}
