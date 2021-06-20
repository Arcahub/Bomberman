/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** DiscordRPCPlugin
*/

#include "plugin/DiscordPlugin.hpp"
#include "discord/discord.h"
#include "ige.hpp"
#include <chrono>
#include <iostream>

using ige::core::App;
using ige::ecs::System;
using ige::ecs::World;

static void init_sdk(World& wld)
{
    const auto p1 = std::chrono::system_clock::now();
    DiscordState& state = wld.emplace<DiscordState>();
    discord::Core* core {};
    auto result = discord::Core::Create(
        855194180761157682, DiscordCreateFlags_Default, &core);

    state.core.reset(core);
    if (!state.core) {
        std::cout << "Failed to instantiate discord core! (err "
                  << static_cast<int>(result) << ")\n";
        wld.remove<DiscordState>();
    } else {
        state.activity.GetTimestamps().SetStart(
            std::chrono::duration_cast<std::chrono::seconds>(
                p1.time_since_epoch())
                .count());
        state.activity.GetAssets().SetLargeImage("bomb_head");
        state.activity.SetState("In the menu");
        state.activity.SetType(discord::ActivityType::Playing);
        state.core->ActivityManager().UpdateActivity(
            state.activity, [](discord::Result result) {});
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
