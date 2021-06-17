#include "bomberman_lobby/packets/PlayerInputsPacket.hpp"
#include "bomberman_lobby/BombermanPacket.hpp"
#include "ige.hpp"

using ige::plugin::input::InputManager;
using ige::plugin::input::InputRegistryState;
using ige::plugin::input::KeyboardKey;

PlayerInputsPacket::PlayerInputsPacket(const InputManager<>& manager)
{
    if (manager.keyboard().is_down(KeyboardKey::KEY_ARROW_UP)) {
        actions.push_back(NetworkController::Actions::UP);
    }

    if (manager.keyboard().is_down(KeyboardKey::KEY_ARROW_DOWN)) {
        actions.push_back(NetworkController::Actions::DOWN);
    }

    if (manager.keyboard().is_down(KeyboardKey::KEY_ARROW_RIGHT)) {
        actions.push_back(NetworkController::Actions::RIGHT);
    }

    if (manager.keyboard().is_down(KeyboardKey::KEY_ARROW_LEFT)) {
        actions.push_back(NetworkController::Actions::LEFT);
    }

    if (manager.keyboard().is_down(KeyboardKey::KEY_SPACE)) {
        actions.push_back(NetworkController::Actions::BOMB);
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

        packet.actions.push_back(static_cast<NetworkController::Actions>(val));
    }
    return packet;
}
