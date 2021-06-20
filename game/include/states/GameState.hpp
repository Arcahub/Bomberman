#ifndef E6F6FCC3_7EFA_4968_A29A_42929BC43BD0
#define E6F6FCC3_7EFA_4968_A29A_42929BC43BD0

#include "ige.hpp"

#include <optional>

class GameState : public ige::core::State {
private:
    std::optional<
        ige::core::EventChannel<ige::plugin::window::WindowEvent>::Subscription>
        m_win_events;

    std::optional<ige::ecs::EntityId> audioSource;
    std::optional<ige::ecs::EntityId> emptyParent;

    ige::plugin::audio::AudioClip::Handle m_music_clip;

public:
    class Loader : public ige::core::State {
    public:
        void on_start(ige::core::App&) override;
    };

    GameState(ige::plugin::audio::AudioClip::Handle music_clip);

    void on_start(ige::core::App&) override;
    void on_update(ige::core::App&) override;
    void on_stop(ige::core::App&) override;
};

#endif /* E6F6FCC3_7EFA_4968_A29A_42929BC43BD0 */
