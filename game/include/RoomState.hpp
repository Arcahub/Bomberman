#ifndef ROOMSTATE_HPP_
#define ROOMSTATE_HPP_

#include "bomberman_lobby/BombermanLobby.hpp"
#include "ige.hpp"

#include <chrono>
#include <optional>
#include <string>

using ige::core::EventChannel;
using ige::core::State;
using ige::ecs::World;
using ige::plugin::window::WindowPlugin;

struct IsServerMarker {
    bool is_server;
};

class RoomState : public ige::core::State {
public:
    void on_start(ige::core::App&) override;
    void on_update(ige::core::App&) override;

private:
    std::optional<
        ige::core::EventChannel<ige::plugin::window::WindowEvent>::Subscription>
        m_win_events;
    bool m_as_client;
    std::string m_mm_id;
};

#endif /* !ROOMSTATE_HPP_ */
