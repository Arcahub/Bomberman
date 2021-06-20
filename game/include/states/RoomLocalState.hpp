#ifndef A8DD0F93_4CC0_4711_89C1_1C7AEEBD42A2
#define A8DD0F93_4CC0_4711_89C1_1C7AEEBD42A2

#include "ige.hpp"
#include "plugin/room/RoomPlayer.hpp"
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>

class RoomLocalState : public ige::core::State {
public:
    void on_start(ige::core::App&) override;
    void on_update(ige::core::App&) override;
    void on_stop(ige::core::App&) override;

private:
    std::optional<
        ige::core::EventChannel<ige::plugin::window::WindowEvent>::Subscription>
        m_win_events;
    bool m_paused = false;
    bool m_skip_first_frame = false;
    std::optional<std::pair<RoomPlayerId, ige::ecs::EntityId>> keyboard_player;
    std::unordered_map<
        ige::plugin::input::ControllerId,
        std::pair<RoomPlayerId, ige::ecs::EntityId>>
        m_players_controller;
};

#endif /* A8DD0F93_4CC0_4711_89C1_1C7AEEBD42A2 */
