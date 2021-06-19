#include "states/GameState.hpp"
#include "bomberman_lobby/BombermanLobby.hpp"
#include "ige.hpp"
#include "scripts/MapGenerator.hpp"
#include "utils/Map.hpp"

using ige::core::App;
using ige::core::EventChannel;
using ige::plugin::audio::AudioClip;
using ige::plugin::audio::AudioSource;
using ige::plugin::render::PerspectiveCamera;
using ige::plugin::script::Scripts;
using ige::plugin::transform::Transform;
using ige::plugin::window::WindowEvent;
using ige::plugin::window::WindowEventKind;

void GameState::on_start(App& app)
{
    auto channel = app.world().get<EventChannel<WindowEvent>>();
    m_win_events.emplace(channel->subscribe());

    auto lobby = app.world().get<BombermanLobby>();
    auto map_ressources = app.world().get<MapRessources>();

    std::shared_ptr<AudioClip> clip(
        new AudioClip("./assets/sound/BombermanRemixSmash.ogg"));
    std::optional<ige::ecs::EntityId> audioSource
        = app.world().create_entity(AudioSource {}, Transform {});
    auto as = app.world().get_component<AudioSource>(audioSource.value());
    as->load_clip(clip);
    as->play();

    Map::LoadMapContent(app.world(), *map_ressources);
    if (lobby) {
        lobby->spawn_players(app.world(), *map_ressources);
    }

    app.world().create_entity(Scripts::from(MapGenerator { app }));
}

void GameState::on_update(App& app)
{
    auto lobby = app.world().get<BombermanLobby>();

    while (const auto& event = m_win_events->next_event()) {
        if (event->kind == WindowEventKind::WindowClose) {
            lobby->leave();
        }
    }
    if (lobby) {
        lobby->update(app.world());
    }
}

void GameState::on_stop(App& app)
{
    for (auto [ent, pos] : app.world().query<Transform>()) {
        app.world().remove_entity(ent);
    }
}