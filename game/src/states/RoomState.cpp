#include "states/RoomState.hpp"
#include "bomberman_lobby/BombermanLobby.hpp"
#include "bomberman_lobby/BombermanPacket.hpp"
#include "ige.hpp"
#include "scripts/AIController.hpp"
#include "scripts/MapGenerator.hpp"
#include "scripts/NetworkController.hpp"
#include "scripts/PlayerController.hpp"
#include "scripts/SoloController.hpp"
#include "scripts/TrackballCamera.hpp"
#include "states/GameState.hpp"
#include "states/MenuState.hpp"
#include "utils/Map.hpp"
#include "utils/Player.hpp"
#include "utils/Tag.hpp"
#include <chrono>
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
    m_as_client = marker ? false : true;

    Map::InitMap(app.world());

    app.world().create_entity(Transform {}, Light::ambient(0.2));
    app.world().create_entity(Transform {}, Light::directional(0.8));

    try {
        if (m_as_client) {
            lobby.join("127.0.0.1", 4200);
            std::cout << "[Lobby] Connected to server, there are "
                      << lobby.clients().size() << " waiting players."
                      << std::endl;
        } else {
            lobby.start(4200);
            lobby.add_player(Player::spawn<SoloController>(app.world()));
            std::cout << "[Lobby] Started as server." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        app.state_machine().pop();
    }
}

void RoomState::on_update(App& app)
{
    if (frame_one == false) {
        frame_one = true;
        return;
    }
    auto lobby = app.world().get<BombermanLobby>();
    while (const auto& event = m_win_events->next_event()) {
        if (event->kind == WindowEventKind::WindowClose) {
            lobby->leave();
        }
    }
    if (lobby) {
        if (lobby->state() == BombermanLobbyState::GAME) {
            app.state_machine();
        }
        lobby->update(app.world());
    }

    auto manager = app.world().get<InputManager<>>();

    if (manager) {
        if (manager->keyboard().is_down(KeyboardKey::KEY_ESCAPE)) {
            app.state_machine().switch_to<MenuState>();
        } else if (manager->keyboard().is_pressed(KeyboardKey::KEY_SPACE)) {
            std::cout << "Switch to game" << std::endl;
            lobby->start_game(app.world());
            app.state_machine().switch_to<GameState>();
        }
    }
}

void RoomState::on_stop(App& app)
{
    // auto map_ressource = app.world().get<MapRessources>();

    // if (map_ressource) {
    //     app.world().remove_entity(map_ressource->map_id);
    // }
}
