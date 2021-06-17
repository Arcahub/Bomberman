/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** DiscordRPCPlugin
*/

#include "plugin/DiscordPlugin.hpp"
#include "discord/discord.h"
#include "ige.hpp"

using ige::core::App;
using ige::ecs::System;
using ige::ecs::World;

struct DiscordState {
    discord::User currentUser;

    std::unique_ptr<discord::Core> core;
};

static void init_sdk(World& wld)
{
    DiscordState state {};
    discord::Core* core {};

    auto result = discord::Core::Create(
        310270644849737729, DiscordCreateFlags_Default, &core);
    state.core.reset(core);
    if (!state.core) {
        std::cout << "Failed to instantiate discord core! (err "
                  << static_cast<int>(result) << ")\n";
        std::exit(-1);
    }
}

void DiscordPlugin::plug(App::Builder& builder) const
{
    builder.add_startup_system(System::from(init_sdk));
}
