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

    Map::LoadMapContent(app.world(), *map_ressources);
    if (lobby) {
        lobby->spawn_players(app.world(), *map_ressources);
    }

    app.world().create_entity(Scripts::from(MapGenerator {}));
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
