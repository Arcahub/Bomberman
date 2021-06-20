#ifndef MENUSTATE_HPP_
#define MENUSTATE_HPP_

#include "ige.hpp"

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
    std::optional<ige::ecs::EntityId> backgroundLayer;
    std::optional<ige::ecs::EntityId> foregroundLayer;
    std::optional<ige::ecs::EntityId> bombLayer;
    std::optional<ige::ecs::EntityId> bombUiLayer;
    std::optional<ige::ecs::EntityId> background;
    std::optional<ige::ecs::EntityId> bombSprite;
    std::optional<ige::ecs::EntityId> playerSprite;
    std::optional<ige::ecs::EntityId> bombMenuLayout;
    std::optional<ige::ecs::EntityId> bombMenuSelect;
    std::optional<ige::ecs::EntityId> audioListener;
    std::optional<ige::ecs::EntityId> audioSource;
};

#endif /* !MENUSTATE_HPP_ */
