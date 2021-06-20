/*
** EPITECH PROJECT, 2021
** Bomberman
** File description:
** DiscordPlugin
*/

#ifndef DISCORDPLUGIN_HPP_
#define DISCORDPLUGIN_HPP_

#include <string>

#include "discord/discord.h"

#include "ige.hpp"
#include "network/NetworkManager.hpp"
#include "network/Server.hpp"

struct DiscordState {
    discord::User currentUser;
    discord::Activity activity;
    std::unique_ptr<discord::Core> core;
};

class DiscordPlugin : public ige::core::App::Plugin {
public:
    void plug(ige::core::App::Builder&) const override;
};

#endif /* !DISCORDPLUGIN_HPP_ */
