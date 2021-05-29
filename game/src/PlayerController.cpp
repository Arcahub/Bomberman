/*
** EPITECH PROJECT, 2021
** PlayerController
** File description:
** PlayerController
*/

#include "PlayerController.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using glm::vec3;
using glm::vec4;
using ige::core::App;
using ige::core::EventChannel;
using ige::core::State;
using ige::ecs::Schedule;
using ige::ecs::World;
using ige::plugin::input::InputManager;
using ige::plugin::input::KeyboardKey;
using ige::plugin::transform::Transform;

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::tick()
{
    auto input = get_resource<InputManager>();

    vec3 direction { 0.0f };

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_UP)) {
        direction.z -= 1.0f;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_DOWN)) {
        direction.z += 1.0f;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_RIGHT)) {
        direction.x += 1.0f;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_LEFT)) {
        direction.x -= 1.0f;
    }

    if (direction != vec3 { 0.0f }) {
        auto xform = get_component<Transform>();

        xform->translate(glm::normalize(direction) * 0.05f);
    }
}