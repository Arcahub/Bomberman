#ifndef E6F6FCC3_7EFA_4968_A29A_42929BC43BD0
#define E6F6FCC3_7EFA_4968_A29A_42929BC43BD0

#include "ige.hpp"

#include <optional>

class GameState : public ige::core::State {
private:
    std::optional<
        ige::core::EventChannel<ige::plugin::window::WindowEvent>::Subscription>
        m_win_events;

    std::optional<ige::ecs::EntityId> m_cube;

public:
    void on_start(ige::core::App&) override;
    void on_update(ige::core::App&) override;
};

#endif /* E6F6FCC3_7EFA_4968_A29A_42929BC43BD0 */
