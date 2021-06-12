#include "plugin/BombermanLobbyPlugin.hpp"
#include "bomberman_lobby/BombermanLobby.hpp"
#include "ige.hpp"

using ige::core::App;
using ige::ecs::System;
using ige::ecs::World;

static void update_lobby(World& wld)
{
    auto lobby = wld.get<BombermanLobby>();

    if (!lobby) {
        return;
    }
    lobby->update(wld);
}

void BombermanLobbyPlugin::plug(App::Builder& builder) const
{
    builder.add_system(System::from(update_lobby));
}
