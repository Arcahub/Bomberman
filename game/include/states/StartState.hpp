#ifndef STARTSTATE_HPP
#define STARTSTATE_HPP

#include "ige.hpp"

#include <optional>

class StartState : public ige::core::State {
private:
    std::optional<
        ige::core::EventChannel<ige::plugin::window::WindowEvent>::Subscription>
        m_win_events;

    std::optional<ige::ecs::EntityId> backgroundLayer;
    std::optional<ige::ecs::EntityId> foregroundLayer;
    std::optional<ige::ecs::EntityId> background;
    std::optional<ige::ecs::EntityId> logo;
    std::optional<ige::ecs::EntityId> press;
    std::optional<ige::ecs::EntityId> audioListener;
    std::optional<ige::ecs::EntityId> audioSource;

public:
    void on_start(ige::core::App&) override;
    void on_update(ige::core::App&) override;
    void on_stop(ige::core::App& app) override;
};

#endif /* STARTSTATE_HPP */
