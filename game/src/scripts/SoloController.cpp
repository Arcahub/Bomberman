#include "scripts/SoloController.hpp"
#include "scripts/PlayerController.hpp"

using ige::core::App;
using ige::core::EventChannel;
using ige::core::State;
using ige::ecs::Schedule;
using ige::plugin::input::ControllerAxis;
using ige::plugin::input::ControllerButton;
using ige::plugin::input::InputManager;
using ige::plugin::input::KeyboardKey;

SoloController::SoloController(
    const std::optional<ige::plugin::input::ControllerId>& controller_id)
{
    m_controller_id = controller_id;
}
SoloController::SoloController(
    int id,
    const std::optional<ige::plugin::input::ControllerId>& controller_id)
    : m_id(id)
{
    m_controller_id = controller_id;
}

std::optional<ige::plugin::input::ControllerId>
SoloController::controller_id() const
{
    return m_controller_id;
}

void SoloController::tick()
{
    ige::plugin::input::InputManager<>* input = get_resource<InputManager<>>();

    SetSoloMovement(input);

    if (m_controller_id) {
        auto controller = input->controller(*m_controller_id);

        if (controller) {
            m_bomb = controller->is_pressed(ControllerButton::A);
        }
    } else {
        m_bomb = input->keyboard().is_pressed(KeyboardKey::KEY_SPACE);
    }
}

void SoloController::SetSoloMovement(ige::plugin::input::InputManager<>* input)
{
    m_direction = { 0.0f, 0.0f };

    if (m_controller_id) {
        auto controller = input->controller(*m_controller_id);

        if (controller) {
            if (controller->get_axis_value(ControllerAxis::LEFT_Y) < -0.5f) {
                m_direction.y -= 1.0f;
            }
            if (controller->get_axis_value(ControllerAxis::LEFT_Y) > 0.5f) {
                m_direction.y += 1.0f;
            }
            if (controller->get_axis_value(ControllerAxis::LEFT_X) > 0.5f) {
                m_direction.x += 1.0f;
            }
            if (controller->get_axis_value(ControllerAxis::LEFT_X) < -0.5f) {
                m_direction.x -= 1.0f;
            }
        }
    } else {
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
}
