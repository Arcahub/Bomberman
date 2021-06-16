#ifndef MENUSTATE_HPP_
#define MENUSTATE_HPP_

#include "ige.hpp"

using ige::core::EventChannel;
using ige::core::State;
using ige::ecs::EntityId;
using ige::ecs::World;
using ige::plugin::window::WindowPlugin;

class MenuState : public ige::core::State {
public:
    void on_start(ige::core::App&) override;
    void on_update(ige::core::App&) override;
    void on_stop(ige::core::App&) override;

protected:
private:
    std::optional<
        ige::core::EventChannel<ige::plugin::window::WindowEvent>::Subscription>
        m_win_events;
    std::optional<ige::ecs::EntityId> background;
    std::optional<ige::ecs::EntityId> bombSprite;
    std::optional<ige::ecs::EntityId> bombMenuLayout;
    std::optional<ige::ecs::EntityId> bombMenuSelect;
    std::optional<ige::ecs::EntityId> audioListener;
    std::optional<ige::ecs::EntityId> audioSource;
};

#endif /* !MENUSTATE_HPP_ */
