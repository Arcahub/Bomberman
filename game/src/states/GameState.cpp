#include "states/GameState.hpp"
#include "bomberman_lobby/BombermanLobby.hpp"
#include "ige.hpp"
#include "scripts/MapGenerator.hpp"
#include "states/LoadingState.hpp"
#include "states/MenuState.hpp"
#include "utils/GameSettings.hpp"
#include "utils/Map.hpp"
#include "utils/Tag.hpp"
#include <iostream>

#ifdef WIN32
#include "plugin/DiscordPlugin.hpp"
#endif

using ige::core::App;
using ige::core::EventChannel;
using ige::plugin::audio::AudioClip;
using ige::plugin::audio::AudioSource;
using ige::plugin::render::PerspectiveCamera;
using ige::plugin::script::Scripts;
using ige::plugin::transform::Parent;
using ige::plugin::transform::RectTransform;
using ige::plugin::transform::Transform;
using ige::plugin::window::WindowEvent;
using ige::plugin::window::WindowEventKind;
using ige::plugin::render::Light;

void GameState::Loader::on_start(ige::core::App& app)
{
    app.state_machine().switch_to<LoadingState<GameState, AudioClip::Handle>>(
        AudioClip::load_async("./assets/sound/BombermanRemixSmash.ogg"));
}

GameState::GameState(AudioClip::Handle music_clip)
    : m_music_clip(music_clip)
{
}

void GameState::on_start(App& app)
{
    auto channel = app.world().get<EventChannel<WindowEvent>>();
    m_win_events.emplace(channel->subscribe());

    auto lobby = app.world().get<BombermanLobby>();
    auto map_ressources = app.world().get<MapRessources>();

    audioSource = app.world().create_entity(AudioSource {}, Transform {});
    auto as = app.world().get_component<AudioSource>(audioSource.value());
    as->load_clip(m_music_clip);
    as->play();

    lights.push_back(app.world().create_entity(Transform {},
        Light::ambient(0.2)));
    lights.push_back(app.world().create_entity(Transform {},
        Light::directional(0.8)));

    Map::LoadMapContent(app.world(), *map_ressources);
    if (lobby) {
        lobby->spawn_players(app.world(), *map_ressources);
    }

    emptyParent = app.world().create_entity(RectTransform {});

    app.world().create_entity(
        Scripts::from(MapGenerator { app, emptyParent }),
        Parent { *emptyParent }, MapGeneratorTag {});
#ifdef WIN32
    DiscordState* state = app.world().get<DiscordState>();

    if (state) {
        state->activity.SetState("In a game");
        state->activity.GetParty().GetSize().SetMaxSize(4);
        state->core->ActivityManager().UpdateActivity(
            state->activity, [](discord::Result result) {});
    }
#endif
}

void GameState::on_update(App& app)
{
    auto gs = app.world().get<GameSettings>();
    auto as = app.world().get_component<AudioSource>(audioSource.value());

    if (as && gs)
        as->set_volume(gs->audio * gs->music);

    auto lobby = app.world().get<BombermanLobby>();

    while (const auto& event = m_win_events->next_event()) {
        if (event->kind == WindowEventKind::WindowClose) {
            lobby->leave();
        }
    }
    if (lobby) {
        if (lobby->disconnected()) {
            app.state_machine().switch_to<MenuState::Loader>();
        }
        lobby->update(app.world());
    }
}

static void safeDelete(App& app, std::optional<ige::ecs::EntityId> entity)
{
    if (entity.has_value())
        app.world().remove_entity(entity.value());
}

void GameState::on_stop(App& app)
{
    safeDelete(app, audioSource);
    safeDelete(app, emptyParent);

    for (auto &ent : lights) {
        safeDelete(app, ent);
    }
    auto map_ressource = app.world().get<MapRessources>();

    if (map_ressource) {
        app.world().remove_entity(map_ressource->map_id);
    }
}
