/*
** EPITECH PROJECT, 2021
** PlayerController
** File description:
** PlayerController
*/

#include "PlayerController.hpp"
#include "Bomb.hpp"

#include <iostream>

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
using ige::plugin::input::InputManager;
using ige::plugin::input::KeyboardKey;
using ige::plugin::render::MeshRenderer;
using ige::plugin::time::Time;
using ige::plugin::transform::Transform;

using ige::plugin::physics::Collider;
using ige::plugin::physics::ColliderType;
using ige::plugin::physics::Constraint;
using ige::plugin::physics::PhysicsWorld;
using ige::plugin::physics::RigidBody;

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
    this->SetEvent();
}

void PlayerController::update()
{
    if (m_life <= 0) {
        world().remove_entity(this->entity());
        return;
    }
}

void PlayerController::SetEvent()
{
    auto input = get_resource<InputManager>();

    this->SetMovement(input);
    this->SetAction(input);
}

void PlayerController::SetAction(auto input)
{
    if (canAction > 0)
        canAction -= get_resource<Time>()->delta_seconds();
    if (input->keyboard().is_down(KeyboardKey::KEY_SPACE) && canAction <= 0) {
        canAction = 7.5f;
        auto playerResources = this->get_or_emplace_resource<PlayerResources>();
        auto xform = get_component<Transform>();
        auto posPlayer = xform->translation();
        Collider boxCollider = { ColliderType::BOX };
        boxCollider.box.extents = { 1.0f, 1.0f, 1.0f };

        this->world().create_entity(
            Transform {}
                .set_translation(vec3 {
                    posPlayer.x,
                    posPlayer.y + 0.0f,
                    posPlayer.z,
                })
                .set_scale(vec3 { 0.5f, 0.5f, 0.5f }),
            RigidBody { boxCollider, 1, false },
            MeshRenderer {
                playerResources->cube_mesh,
                playerResources->ground_mat,
            },
            Scripts::from(Bomb { m_blockMuds, m_posBlockMuds }));
    }
}

void PlayerController::SetMovement(auto input)
{
    vec3 direction { 0.0f };
    vec3 rotation { 0.0f };

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_UP)) {
        direction.z -= 1.0f;
        rotation.y += 180;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_DOWN)) {
        direction.z += 1.0f;
        rotation.y += 0;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_RIGHT)) {
        direction.x += 1.0f;
        rotation.y += 90;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_LEFT)) {
        direction.x -= 1.0f;
        rotation.y += 270;
    }

    if (rotation != vec3 { 0.0f }) {
        auto xform = get_component<Transform>();

        xform->set_rotation(rotation);
    }
    if (direction != vec3 { 0.0f }) {
        auto rigidBody = get_component<RigidBody>();

        rigidBody->apply_force(glm::normalize(direction) * 0.25f);
    }
}