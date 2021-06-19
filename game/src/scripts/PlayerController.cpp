#include "scripts/PlayerController.hpp"
#include "scripts/AIController.hpp"
#include "scripts/Bomb.hpp"
#include "scripts/MapGenerator.hpp"
#include "scripts/NetworkController.hpp"
#include "scripts/SoloController.hpp"
#include "utils/Tag.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <iostream>

#include <iostream>

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
using ige::plugin::transform::Children;
using ige::plugin::transform::Parent;
using ige::plugin::transform::Transform;

using ige::plugin::physics::Collider;
using ige::plugin::physics::ColliderType;
using ige::plugin::physics::Constraint;
using ige::plugin::physics::PhysicsWorld;
using ige::plugin::physics::RigidBody;

using ige::plugin::animation::Animator;
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

void PlayerController::update()
{
    auto children = get_component<Children>();

    for (auto child : children->entities) {
        auto animator = world().get_component<Animator>(child);

        if (animator && !animator->empty()) {
            switch (statePlayer) {
            case stateAnim::Idle:
                if (animator->track_count() >= 1) {
                    animator->set_current(1);
                }
                break;
            case stateAnim::Run:
                animator->set_current(0);
                std::cout << " !! " << animator->track_count() << std::endl;
                /*if (animator->track_count() >= 2) {
                    animator->set_current(2);
                    animator->track(2);
                }*/
                break;
            case stateAnim::Attack:
                if (animator->track_count() >= 3) {
                    animator->set_current(3);
                }
                break;
            default:
                animator->set_current(0);
                break;
            }

            animator->playback_rate = 1.0f;
        }
    }

    this->SetEvent();
    if (m_life <= 0) {
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
    } else {
        std::cerr << "[Player Controller] No subcontroller has been set."
                  << std::endl;
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
        auto xform = get_component<Transform>();
        auto player_pos = xform->translation();
        Collider sphereCollider = { ColliderType::SPHERE };

        canAction = m_actionSpeed;
        sphereCollider.sphere.radius = 0.85f;

        statePlayer = stateAnim::Attack;
        this->world().create_entity(
            Transform::from_pos(vec3 {
                                    player_pos.x + 0.5f,
                                    player_pos.y,
                                    player_pos.z,
                                })
                .set_scale(vec3 { 0.4f, 0.4f, 0.4f }),
            RigidBody { sphereCollider, 1, false },
            GltfScene { "assets/Models/bomb.glb", GltfFormat::BINARY },
            BombTag {}, Scripts::from(Bomb {}));
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

        statePlayer = stateAnim::Run;
        rigidBody->set_velocity(glm::normalize(direction) * m_speed);
    } else {
        auto rigidBody = get_component<RigidBody>();

        statePlayer = stateAnim::Idle;
        rigidBody->set_velocity(vec3 { 0.0f });
    }
}
