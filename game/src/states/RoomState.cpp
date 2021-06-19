#include "states/RoomState.hpp"
#include "bomberman_lobby/BombermanLobby.hpp"
#include "ige.hpp"
#include "matchmaking/Matchmaking.hpp"
#include "states/GameState.hpp"
#include "states/MenuState.hpp"
#include "utils/Map.hpp"
#include "utils/Player.hpp"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <optional>

using glm::vec3;
using ige::core::App;
using ige::core::EventChannel;
using ige::ecs::EntityId;
using ige::ecs::World;
using ige::plugin::gltf::GltfFormat;
using ige::plugin::gltf::GltfScene;
using ige::plugin::input::InputManager;
using ige::plugin::input::KeyboardKey;
using ige::plugin::physics::Collider;
using ige::plugin::physics::ColliderType;
using ige::plugin::physics::RigidBody;
using ige::plugin::render::Light;
using ige::plugin::render::PerspectiveCamera;
using ige::plugin::script::Scripts;
using ige::plugin::transform::Parent;
using ige::plugin::transform::Transform;
using ige::plugin::window::WindowEvent;
using ige::plugin::window::WindowEventKind;

#include <iostream>

bool frame_one = false;

void RoomState::on_start(App& app)
{
    auto& lobby = app.world().emplace<BombermanLobby>();
    auto marker = app.world().get<IsServerMarker>();
    auto channel = app.world().get<EventChannel<WindowEvent>>();

    m_win_events.emplace(channel->subscribe());
    m_as_client = marker && marker->is_client ? true : false;

    Map::InitMap(app.world());

    app.world().create_entity(Transform {}, Light::ambient(0.2));
    app.world().create_entity(Transform {}, Light::directional(0.8));

    try {
        if (this->m_as_client) {
            auto server_data = Matchmaking::GetBestFitServer();

            lobby.join(server_data.ip, server_data.port);
            std::cout << "[Lobby] Connected to server, there are "
                      << lobby.clients().size() << " waiting players."
                      << std::endl;
        } else {
            lobby.start(4200);
            lobby.add_player(Player::spawn<SoloController>(
                app.world(), glm::vec3 { 7.0f, 2.0f, 7.0f }));
            this->m_mm_id = Matchmaking::RegisterServer("127.0.0.1", 4200);
            std::cout << "[Lobby] Started as server." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        app.state_machine().switch_to<MenuState>();
    }
}

void RoomState::on_update(App& app)
{
    if (m_paused) {
        return;
    }
    if (frame_one == false) {
        frame_one = true;
        return;
    }

    auto lobby = app.world().get<BombermanLobby>();
    while (const auto& event = m_win_events->next_event()) {
        if (event->kind == WindowEventKind::WindowClose) {
            if (!m_as_client)
                Matchmaking::UnRegisterServer(this->m_mm_id);
            if (lobby)
                lobby->leave();
        }
    }
    if (lobby) {
        if (lobby->disconnected()) {
            app.state_machine().switch_to<MenuState>();
        }
        if (lobby->state() == BombermanLobbyState::GAME) {
            std::cout << "Switch to game" << std::endl;
            m_paused = true;
            app.state_machine().push<GameState>();
        }
        lobby->update(app.world());
    }

    auto manager = app.world().get<InputManager<>>();

    if (manager) {
        if (manager->keyboard().is_down(KeyboardKey::KEY_ESCAPE)) {
            lobby->leave();
            app.state_machine().switch_to<MenuState>();
        } else if (manager->keyboard().is_pressed(KeyboardKey::KEY_SPACE)) {
            lobby->start_game(app.world());
        }
    }
}

void RoomState::on_stop(App& app)
{
    auto map_ressource = app.world().get<MapRessources>();

    if (map_ressource) {
        // Delete map
    }
}
