#include "bomberman_lobby/packets/PlayerInputsPacket.hpp"
#include "bomberman_lobby/BombermanPacket.hpp"
#include "ige.hpp"

using ige::plugin::input::InputManager;
using ige::plugin::input::InputRegistryState;
using ige::plugin::input::KeyboardKey;

PlayerInputsPacket::PlayerInputsPacket(const InputManager<>& manager)
{
    if (manager.keyboard().is_pressed(KeyboardKey::KEY_ARROW_UP)) {
        actions.push_back(NetworkController::ActionUpdateStates::UP_PRESSED);
    } else if (manager.keyboard().is_released(KeyboardKey::KEY_ARROW_UP)) {
        actions.push_back(NetworkController::ActionUpdateStates::UP_RELEASED);
    }

    if (manager.keyboard().is_pressed(KeyboardKey::KEY_ARROW_DOWN)) {
        actions.push_back(NetworkController::ActionUpdateStates::DOWN_PRESSED);
    } else if (manager.keyboard().is_released(KeyboardKey::KEY_ARROW_DOWN)) {
        actions.push_back(NetworkController::ActionUpdateStates::DOWN_RELEASED);
    }

    if (manager.keyboard().is_pressed(KeyboardKey::KEY_ARROW_RIGHT)) {
        actions.push_back(NetworkController::ActionUpdateStates::RIGHT_PRESSED);
    } else if (manager.keyboard().is_released(KeyboardKey::KEY_ARROW_RIGHT)) {
        actions.push_back(
            NetworkController::ActionUpdateStates::RIGHT_RELEASED);
    }

    if (manager.keyboard().is_pressed(KeyboardKey::KEY_ARROW_LEFT)) {
        actions.push_back(NetworkController::ActionUpdateStates::LEFT_PRESSED);
    } else if (manager.keyboard().is_released(KeyboardKey::KEY_ARROW_LEFT)) {
        actions.push_back(NetworkController::ActionUpdateStates::LEFT_RELEASED);
    }

    if (manager.keyboard().is_pressed(KeyboardKey::KEY_SPACE)) {
        actions.push_back(NetworkController::ActionUpdateStates::BOMB_ACTION);
    }
}

std::vector<char> PlayerInputsPacket::serialize()
{
    std::vector<char> data;

    serialize(data);
    return data;
}

// Currently serialize from InputManageer but need to change to handle multiple
// device
void PlayerInputsPacket::serialize(std::vector<char>& buff)
{
    buff.push_back(static_cast<char>(BombermanPacketType::PLAYER_INPUTS));
    for (auto& action : actions) {
        buff.push_back(static_cast<char>(action));
    }
}

PlayerInputsPacket
PlayerInputsPacket::deserialize(const std::vector<char>& data)
{
    PlayerInputsPacket packet;
    bool type_parsed = false;

    packet.actions.clear();
    for (auto& val : data) {
        if (!type_parsed) {
            type_parsed = true;
            continue;
        }

        packet.actions.push_back(
            static_cast<NetworkController::ActionUpdateStates>(val));
    }
    return packet;
}
