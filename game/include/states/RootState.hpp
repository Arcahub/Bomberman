#ifndef E9E525B6_4033_412F_B22A_6CAF4BA3B7DE
#define E9E525B6_4033_412F_B22A_6CAF4BA3B7DE

#include "ige.hpp"

#include <optional>

class RootState : public ige::core::State {
private:
    std::optional<
        ige::core::EventChannel<ige::plugin::window::WindowEvent>::Subscription>
        m_win_events;

    std::optional<ige::ecs::EntityId> m_cube;

public:
    void on_start(ige::core::App&) override;
    void on_update(ige::core::App&) override;
    void on_stop(ige::core::App& app) override;
};

#endif /* E9E525B6_4033_412F_B22A_6CAF4BA3B7DE */
