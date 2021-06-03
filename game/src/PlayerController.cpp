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
using ige::plugin::transform::Transform;

struct PlayerResources {
    PlayerResources()
    {
        cube_mesh = Mesh::make_cube(1.0f);
        ground_mat = Material::make_default();
    }

    std::shared_ptr<Mesh> cube_mesh;
    std::shared_ptr<Material> ground_mat;
};

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::tick()
{
    this->SetEvent();
}

void PlayerController::SetEvent()
{
    auto input = get_resource<InputManager>();

    this->SetMovement(input);
    this->SetAction(input);
}

void PlayerController::SetAction(auto input)
{
    if (input->keyboard().is_down(KeyboardKey::KEY_SPACE)) {
        auto playerResources = this->get_or_emplace_resource<PlayerResources>();
        auto xform = get_component<Transform>();
        auto posPlayer = vec4(0, 0, 0, 1) * xform->local_to_world();

        std::cout << "!!" << posPlayer.x << std::endl;
        this->world().create_entity(
            Transform {}
                .set_translation(vec3 {
                    posPlayer.x,
                    posPlayer.y + 1.0f,
                    posPlayer.z,
                })
                .set_scale(vec3 { 1.0f, 1.0f, 1.0f }),
            MeshRenderer {
                playerResources->cube_mesh,
                playerResources->ground_mat,
            },
            Scripts::from(Bomb {}));
    }
}

void PlayerController::SetMovement(auto input)
{
    vec3 direction { 0.0f };
    vec3 rotation { 0.0f };

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_UP)) {
        direction.z -= 1.0f;
        rotation.y += 141.3716694115;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_DOWN)) {
        direction.z += 1.0f;
        rotation.y += 0;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_RIGHT)) {
        direction.x += 1.0f;
        rotation.y += 70.68583470577;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_LEFT)) {
        direction.x -= 1.0f;
        rotation.y += 212.0575041173;
    }

    if (direction != vec3 { 0.0f }) {
        auto xform = get_component<Transform>();

        xform->translate(glm::normalize(direction) * 0.05f);
        xform->set_rotation(rotation);
    }
}