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

static void init_sdk(World& wld)
{
    DiscordState& state = wld.emplace<DiscordState>();
    discord::Core* core {};
    discord::Activity activity {};
    auto result = discord::Core::Create(
        855194180761157682, DiscordCreateFlags_Default, &core);

    state.core.reset(core);
    if (!state.core) {
        std::cout << "Failed to instantiate discord core! (err "
                  << static_cast<int>(result) << ")\n";
        wld.remove<DiscordState>();
    } else {
        activity.SetState("Waiting in a lobby...");
        activity.SetType(discord::ActivityType::Playing);
        state.core->ActivityManager().UpdateActivity(
            activity, [](discord::Result result) {});
    }
}

static void update_sdk(World& wld)
{
    DiscordState* state = wld.get<DiscordState>();

    if (state) {
        state->core->RunCallbacks();
    }
}

void DiscordPlugin::plug(App::Builder& builder) const
{
    builder.add_startup_system(System::from(init_sdk));
    builder.add_system(System::from(update_sdk));
}
