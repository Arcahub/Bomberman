#include "plugin/BombermanLobbyPlugin.hpp"
#include "bomberman_lobby/BombermanLobby.hpp"
#include "ige.hpp"

using ige::core::App;
using ige::ecs::System;
using ige::ecs::World;

BombermanLobby* client = nullptr;
BombermanLobby* server = nullptr;

bool is_client = false;

static void init_lobby(World& wld)
{
    if (is_client) {
        client = new BombermanLobby();
        client->join("127.0.0.1", 4200);
    } else {
        server = new BombermanLobby();
        server->start(4200);
    }
}

static void update_lobby(World& wld)
{
    if (is_client)
        client->update(wld);
    else
        server->update(wld);
}

void BombermanLobbyPlugin::plug(App::Builder& builder) const
{
    is_client = m_is_client;
    builder.add_startup_system(System::from(init_lobby));
    builder.add_system(System::from(update_lobby));
}
