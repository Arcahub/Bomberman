#include "plugin/NetworkPlugin.hpp"
#include "ige.hpp"

#include <arpa/inet.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

using ige::core::App;
using ige::ecs::System;
using ige::ecs::World;

static int client = 0;
static int server = 0;
static int server_client = 0;

static void init_network(World& wld)
{
    wld.emplace<NetworkManager>();
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
    builder.add_system(System(update_network_manager));
}
