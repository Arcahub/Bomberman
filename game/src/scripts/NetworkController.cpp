#include <algorithm>

#include "ige.hpp"
#include "scripts/NetworkController.hpp"
#include "scripts/PlayerController.hpp"

using ige::plugin::input::InputManager;
using ige::plugin::input::KeyboardKey;

NetworkController::NetworkController(int id)
    : m_id(id)
{
}

void NetworkController::tick()
{
    m_bomb = false;
    m_direction = { 0.0f, 0.0f };

    for (auto update_state : update_states) {
        switch (update_state) {
        case UP_PRESSED:
        case UP_RELEASED:
            actions[Action::UP] = update_state == UP_PRESSED;
            break;
        case DOWN_PRESSED:
        case DOWN_RELEASED:
            actions[Action::DOWN] = update_state == DOWN_PRESSED;
            break;
        case LEFT_PRESSED:
        case LEFT_RELEASED:
            actions[Action::LEFT] = update_state == LEFT_PRESSED;
            break;
        case RIGHT_PRESSED:
        case RIGHT_RELEASED:
            actions[Action::RIGHT] = update_state == RIGHT_PRESSED;
            break;
        case BOMB_ACTION:
            actions[Action::BOMB] = 1;
        }
    }
    for (auto& action : actions) {
        if (action.first == Action::LEFT && action.second) {
            m_direction.x -= 1.0f;
        }
        if (action.first == Action::RIGHT && action.second) {
            m_direction.x += 1.0f;
        }
        if (action.first == Action::UP && action.second) {
            m_direction.y -= 1.0f;
        }
        if (action.first == Action::DOWN && action.second) {
            m_direction.y += 1.0f;
        }
        if (action.first == Action::BOMB && action.second) {
            m_bomb = true;
        }
    }
    actions[Action::BOMB] = false;
    update_states.clear();
}
