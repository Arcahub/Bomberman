#include "scripts/PlayerController.hpp"
#include "Tag.hpp"
#include "scripts/AIController.hpp"
#include "scripts/Bomb.hpp"
#include "scripts/MapGenerator.hpp"
#include "scripts/NetworkController.hpp"
#include "scripts/SoloController.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using glm::vec3;
using glm::vec4;
using ige::asset::Material;
using ige::asset::Mesh;
using ige::core::App;
using ige::core::EventChannel;
using ige::core::State;
using ige::ecs::Schedule;
using ige::ecs::World;
using ige::plugin::render::MeshRenderer;
using ige::plugin::time::Time;
using ige::plugin::transform::Transform;

using ige::plugin::physics::Collider;
using ige::plugin::physics::ColliderType;
using ige::plugin::physics::Constraint;
using ige::plugin::physics::PhysicsWorld;
using ige::plugin::physics::RigidBody;

using ige::plugin::gltf::GltfFormat;
using ige::plugin::gltf::GltfScene;

struct PlayerResources {
    PlayerResources()
    {
        cube_mesh = Mesh::make_cube(1.0f);
        ground_mat = Material::make_default();
    }

    std::shared_ptr<Mesh> cube_mesh;
    std::shared_ptr<Material> ground_mat;
};

PlayerController::PlayerController(
    std::vector<ige::ecs::EntityId> blockMuds,
    std::vector<glm::vec2> posBlockMuds)
{
    m_blockMuds = blockMuds;
    m_posBlockMuds = posBlockMuds;
}

PlayerController::~PlayerController()
{
}

void PlayerController::tick()
{
    if (m_life <= 0) {
        auto scp = get_component<Scripts>();
        auto mapGenerator = scp->get<MapGenerator>();

        mapGenerator->numberPlayer--;
    }
}

void PlayerController::update()
{
    this->SetEvent();
    if (m_life <= 0) {
        std::cout << m_life << std::endl;
        world().remove_entity(this->entity());
        return;
    }
}

void PlayerController::SetEvent()
{
    auto scp = get_component<Scripts>();
    auto controllerSolo = scp->get<SoloController>();
    auto controllerAI = scp->get<AIController>();
    auto controllerNet = scp->get<NetworkController>();
    glm::vec2 direction = {};

    if (controllerSolo != nullptr) {
        direction = controllerSolo->m_direction;
        this->SetAction(controllerSolo->m_bomb);
    } else if (controllerAI != nullptr) {
        direction = controllerAI->m_direction;
        this->SetAction(controllerAI->m_bomb);
    } else if (controllerNet) {
        direction = controllerNet->m_direction;
        this->SetAction(controllerNet->m_bomb);
    }
    if (direction != glm::vec2 { 0.0f }) {
        glm::vec2 velocity = glm::normalize(direction) * 2.f;

        this->SetMovement(velocity);
    } else {
        this->SetMovement(glm::vec2 { 0.0f });
    }
}

void PlayerController::SetAction(bool bomb)
{
    if (canAction > 0)
        canAction -= get_resource<Time>()->delta_seconds();
    if (bomb == true && canAction <= 0) {
        auto playerResources = this->get_or_emplace_resource<PlayerResources>();
        auto xform = get_component<Transform>();
        auto posPlayer = xform->translation();
        Collider sphereCollider = { ColliderType::SPHERE };

        canAction = m_actionSpeed;
        sphereCollider.sphere.radius = 0.85f;

        this->world().create_entity(
            Transform {}
                .set_translation(vec3 {
                    posPlayer.x + 0.5f,
                    posPlayer.y,
                    posPlayer.z,
                })
                .set_scale(vec3 { 0.4f, 0.4f, 0.4f }),
            RigidBody { sphereCollider, 1, false },
            GltfScene { "assets/Models/bomb.glb", GltfFormat::BINARY },
            BombTag {}, Scripts::from(Bomb { m_blockMuds, m_posBlockMuds }));
    }
}

void PlayerController::SetMovement(glm::vec2 input)
{
    auto xform = get_component<Transform>();
    vec3 direction { 0.0f };
    vec3 rotation { 0.0f };

    direction.z = input.y;
    direction.x = input.x;
    rotation.y = glm::degrees(glm::atan(-input.y, input.x)) + 90.0f;

    if (m_reverseControlle == true) {
        direction = { direction.x * -1, direction.y * -1, direction.z * -1 };
        reverseCount -= get_resource<Time>()->delta_seconds();
    }
    if (reverseCount <= 0) {
        m_reverseControlle = false;
        reverseCount = 20.0f;
    }

    if (direction != vec3 { 0.0f }) {
        rotationSave = rotation;
        xform->set_rotation(rotation);
    } else
        xform->set_rotation(rotationSave);

    if (direction != vec3 { 0.0f }) {
        auto rigidBody = get_component<RigidBody>();

        rigidBody->set_velocity(glm::normalize(direction) * m_speed);
    } else {
        auto rigidBody = get_component<RigidBody>();

        rigidBody->set_velocity(vec3 { 0.0f });
    }
}
