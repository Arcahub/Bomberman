/*
** EPITECH PROJECT, 2021
** SoloController
** File description:
** SoloController
*/

#include "SoloController.hpp"
#include "PlayerController.hpp"

using ige::core::App;
using ige::core::EventChannel;
using ige::core::State;
using ige::ecs::Schedule;
using ige::plugin::input::InputManager;
using ige::plugin::input::KeyboardKey;

SoloController::SoloController()
{
}

SoloController::~SoloController()
{
}

void SoloController::tick()
{
    SetSoloMovement();
}

void SoloController::SetSoloMovement()
{
    auto input = get_resource<InputManager>();

    m_direction = { 0.0f, 0.0f };

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_UP)) {
        m_direction.y -= 1.0f;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_DOWN)) {
        m_direction.y += 1.0f;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_RIGHT)) {
        m_direction.x += 1.0f;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_LEFT)) {
        m_direction.x -= 1.0f;
    }
}