#ifndef ROOMSTATE_HPP_
#define ROOMSTATE_HPP_

#include "ige.hpp"
#include <optional>
#include <string>

class RoomState : public ige::core::State {
public:
    RoomState(bool is_client = false);

    void on_start(ige::core::App&) override;
    void on_update(ige::core::App&) override;
    void on_stop(ige::core::App&) override;

private:
    std::optional<
        ige::core::EventChannel<ige::plugin::window::WindowEvent>::Subscription>
        m_win_events;
    std::vector<std::optional<ige::ecs::EntityId>> lights;
    bool m_as_client;
    bool m_paused = false;
    std::string m_mm_id;
    bool m_skip_first_frame = false;
};

#endif /* !ROOMSTATE_HPP_ */
