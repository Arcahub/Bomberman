#include "scripts/NetworkController.hpp"
#include "ige.hpp"
#include "scripts/PlayerController.hpp"

using ige::plugin::input::InputManager;
using ige::plugin::input::KeyboardKey;

void NetworkController::tick()
{
    m_bomb = false;

    m_direction = { 0.0f, 0.0f };
    for (auto& action : actions) {
        switch (action) {
        case Actions::LEFT:
            m_direction.x -= 1.0f;
            break;
        case Actions::RIGHT:
            m_direction.x += 1.0f;
            break;
        case Actions::UP:
            m_direction.y -= 1.0f;
            break;
        case Actions::DOWN:
            m_direction.y += 1.0f;
            break;
        case Actions::BOMB:
            m_bomb = true;
        default:
            break;
        }
    }
    actions.clear();
}
