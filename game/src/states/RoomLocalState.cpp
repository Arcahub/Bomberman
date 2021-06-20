#include "states/RoomLocalState.hpp"
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
using ige::plugin::input::ControllerButton;
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

void RoomLocalState::on_start(App& app)
{
    m_skip_first_frame = false;
    auto& lobby = app.world().emplace<BombermanLobby>();
    auto channel = app.world().get<EventChannel<WindowEvent>>();

    m_win_events.emplace(channel->subscribe());

    Map::InitMap(app.world());

    app.world().create_entity(Transform {}, Light::ambient(0.2));
    app.world().create_entity(Transform {}, Light::directional(0.8));

    std::cout << "HEEEYY" << std::endl;
    try {
        lobby.start();
        std::cout << "[Lobby] Started as local." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        app.state_machine().switch_to<MenuState>();
    }
}

void RoomLocalState::on_update(App& app)
{
    if (m_paused) {
        return;
    }
    if (m_skip_first_frame == false) {
        m_skip_first_frame = true;
        return;
    }

    auto lobby = app.world().get<BombermanLobby>();
    while (const auto& event = m_win_events->next_event()) {
        if (event->kind == WindowEventKind::WindowClose) {
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
        if (manager->keyboard().is_pressed(KeyboardKey::KEY_TAB)) {
            if (!keyboard_player && lobby->players_count() < 4) {
                auto player_entity = Player::spawn(
                    app.world(), SoloController {},
                    glm::vec3 { 7.0f, 2.0f, 7.0f });
                auto player_id = lobby->add_player(player_entity);
                if (player_id) {
                    keyboard_player
                        = std::pair<RoomPlayerId, EntityId> { player_id->id,
                                                              player_entity };
                } else {
                    app.world().remove_entity(player_entity);
                }
            }
        } else if (manager->keyboard().is_pressed(
                       KeyboardKey::KEY_BACK_SPACE)) {
            if (keyboard_player) {
                app.world().remove_entity(keyboard_player->second);
                lobby->remove_player(keyboard_player->first);
                keyboard_player = std::nullopt;
            }
        }

        auto controllers = manager->controllers();
        for (auto controller = controllers.first;
             controller != controllers.second; controller++) {
            if (controller->second.is_pressed(ControllerButton::A)) {
                auto player = m_players_controller.find(controller->first);

                if (player == m_players_controller.end()) {
                    auto player_entity = Player::spawn(
                        app.world(), SoloController { controller->first },
                        glm::vec3 { 7.0f, 2.0f, 7.0f });
                    auto player_id = lobby->add_player(player_entity);
                    if (player_id) {
                        m_players_controller.emplace(
                            controller->first,
                            std::pair<RoomPlayerId, EntityId> {
                                player_id->id, player_entity });
                    } else {
                        app.world().remove_entity(player_entity);
                    }
                }
            } else if (controller->second.is_pressed(ControllerButton::B)) {
                auto player = m_players_controller.find(controller->first);

                if (player != m_players_controller.end()) {
                    app.world().remove_entity(player->second.second);
                    lobby->remove_player(player->second.first);
                    keyboard_player = std::nullopt;
                    m_players_controller.erase(controller->first);
                }
            }
        }
    }

    if (manager->keyboard().is_pressed(KeyboardKey::KEY_ESCAPE)) {
        lobby->leave();
        app.state_machine().switch_to<MenuState>();
    } else if (manager->keyboard().is_pressed(KeyboardKey::KEY_SPACE)) {
        lobby->start_game(app.world());
    }
}

void RoomLocalState::on_stop(App& app)
{
    auto map_ressource = app.world().get<MapRessources>();

    if (map_ressource) {
        app.world().remove_entity(map_ressource->map_id);
    }
}
