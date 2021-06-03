#include "scripts/PlayerController.hpp"
#include "ige.hpp"
#include "scripts/CharacterController.hpp"
#include <iostream>

using ige::plugin::input::InputManager;
using ige::plugin::input::KeyboardKey;

void PlayerController::update()
{
    auto input = get_resource<InputManager>();
    auto controller = get_script<CharacterController>();

    if (!controller) {
        std::cout << "no character controller found!" << std::endl;
        return;
    }

    controller->running
        = input->keyboard().is_down(KeyboardKey::KEY_SHIFT_LEFT);

    controller->direction = { 0.0f, 0.0f };

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_UP)) {
        controller->direction.y -= 1.0f;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_DOWN)) {
        controller->direction.y += 1.0f;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_RIGHT)) {
        controller->direction.x += 1.0f;
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_LEFT)) {
        controller->direction.x -= 1.0f;
    }

    controller->jump = input->keyboard().is_down(KeyboardKey::KEY_SPACE);
}
