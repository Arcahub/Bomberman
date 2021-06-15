#ifndef MENUSTATE_HPP_
#define MENUSTATE_HPP_

#include "ige.hpp"

using ige::core::EventChannel;
using ige::core::State;
using ige::ecs::World;
using ige::plugin::window::WindowPlugin;

class MenuState : public ige::core::State {
public:
    void on_start(ige::core::App&) override;
    void on_update(ige::core::App&) override;

protected:
private:
    ige::ecs::EntityId play_ent;

    std::optional<
        ige::core::EventChannel<ige::plugin::window::WindowEvent>::Subscription>
        m_win_events;
};

#endif /* !MENUSTATE_HPP_ */
