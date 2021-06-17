#include "states/GameState.hpp"
#include "ige.hpp"
#include "scripts/MapGenerator.hpp"
#include "utils/Map.hpp"

using ige::core::App;
using ige::core::EventChannel;
using ige::plugin::audio::AudioClip;
using ige::plugin::audio::AudioSource;
using ige::plugin::render::Light;
using ige::plugin::render::PerspectiveCamera;
using ige::plugin::script::Scripts;
using ige::plugin::transform::Transform;
using ige::plugin::window::WindowEvent;
using ige::plugin::window::WindowEventKind;

void GameState::on_start(App& app)
{
    auto channel = app.world().get<EventChannel<WindowEvent>>();
    m_win_events.emplace(channel->subscribe());

    std::shared_ptr<AudioClip> clip(
        new AudioClip("./assets/sound/BombermanRemixSmash.ogg"));
    audioSource = app.world().create_entity(AudioSource {}, Transform {});
    auto as = app.world().get_component<AudioSource>(audioSource.value());
    as->load_clip(clip);
    as->play();

    app.world().create_entity(Scripts::from(MapGenerator {}));

    app.world().create_entity(Transform {}, Light::ambient(0.2));
    app.world().create_entity(Transform {}, Light::directional(0.8));
}

void GameState::on_update(App& app)
{
    while (const auto& event = m_win_events->next_event()) {
        if (event->kind == WindowEventKind::WindowClose) {
            app.quit();
        }
    }
}
