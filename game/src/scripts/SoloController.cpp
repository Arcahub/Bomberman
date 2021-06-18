#include "scripts/SoloController.hpp"
#include "scripts/PlayerController.hpp"

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
    ige::plugin::input::InputManager<>* input = get_resource<InputManager<>>();

    SetSoloMovement(input);

    m_bomb = input->keyboard().is_down(KeyboardKey::KEY_SPACE);
}

void SoloController::SetSoloMovement(ige::plugin::input::InputManager<>* input)
{
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
