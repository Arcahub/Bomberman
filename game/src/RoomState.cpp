#include "RoomState.hpp"
#include "Tag.hpp"
#include "bomberman_lobby/BombermanLobby.hpp"
#include "bomberman_lobby/BombermanPacket.hpp"
#include "ige.hpp"
#include "scripts/AIController.hpp"
#include "scripts/MapGenerator.hpp"
#include "scripts/NetworkController.hpp"
#include "scripts/PlayerController.hpp"
#include "scripts/SoloController.hpp"
#include "scripts/TrackballCamera.hpp"
#include "utils/map/MapGeneration.hpp"
#include "utils/map/MapLoading.hpp"
#include <chrono>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <optional>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using ige::asset::Material;
using ige::asset::Mesh;
using ige::asset::Texture;
using ige::core::App;
using ige::core::EventChannel;
using ige::core::State;
using ige::ecs::EntityId;
using ige::ecs::Schedule;
using ige::ecs::World;
using ige::plugin::gltf::GltfFormat;
using ige::plugin::gltf::GltfPlugin;
using ige::plugin::gltf::GltfScene;
using ige::plugin::input::InputManager;
using ige::plugin::input::InputPlugin;
using ige::plugin::input::KeyboardKey;
using ige::plugin::physics::Collider;
using ige::plugin::physics::ColliderType;
using ige::plugin::physics::PhysicsWorld;
using ige::plugin::physics::RigidBody;
using ige::plugin::render::MeshRenderer;
using ige::plugin::render::PerspectiveCamera;
using ige::plugin::render::RenderPlugin;
using ige::plugin::script::CppBehaviour;
using ige::plugin::script::ScriptPlugin;
using ige::plugin::script::Scripts;
using ige::plugin::time::TimePlugin;
using ige::plugin::transform::Parent;
using ige::plugin::transform::Transform;
using ige::plugin::transform::TransformPlugin;
using ige::plugin::window::WindowEvent;
using ige::plugin::window::WindowEventKind;
using ige::plugin::window::WindowPlugin;
using ige::plugin::window::WindowSettings;

static EntityId spawn_player(World& wld, bool local = true)
{
    Collider boxCollider = { ColliderType::BOX };
    boxCollider.box.extents = { 0.25f, 0.25f, 0.25f };

    if (local) {
        auto playerRoot = wld.create_entity(
            Transform::from_pos(vec3(0.0f, 5.0f, 0.0f)),
            RigidBody { boxCollider }, Player {},
            Scripts::from(SoloController {}, PlayerController {}));

        wld.create_entity(
            Transform::from_pos(vec3(0.0f, -0.667f, 0.0f)).set_scale(0.25f),
            GltfScene {
                "assets/Bomberman_Play.glb",
                GltfFormat::BINARY,
            },
            Parent { playerRoot });
        return playerRoot;

    } else {
        auto playerRoot = wld.create_entity(
            Transform::from_pos(vec3(0.0f, 5.0f, 0.0f)),
            RigidBody {
                boxCollider,
            },
            Player {},
            Scripts::from(NetworkController {}, PlayerController {}));

        wld.create_entity(
            Transform::from_pos(vec3(0.0f, -0.667f, 0.0f)).set_scale(0.25f),
            GltfScene {
                "assets/Bomberman_Play.glb",
                GltfFormat::BINARY,
            },
            Parent { playerRoot });
        return playerRoot;
    }
}

void RoomState::on_start(App& app)
{
    auto& lobby = app.world().emplace<BombermanLobby>();
    auto marker = app.world().get<IsServerMarker>();

    spawn_player(app.world());
    this->m_as_client = marker ? !marker->is_server : true;
    try {
        if (this->m_as_client) {
            lobby.join("127.0.0.1", 4200);
            std::cout << "[Lobby] Connected to server, there are "
                      << lobby.clients().size() << " waiting players."
                      << std::endl;
        } else {
            lobby.start(4200);
            std::cout << "[Lobby] Started as server." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        app.state_machine().pop();
    }
}

void RoomState::on_update(App& app)
{
    auto lobby = app.world().get<BombermanLobby>();

    if (lobby)
        lobby->update(app.world());
}
