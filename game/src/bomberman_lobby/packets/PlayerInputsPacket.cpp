#include "bomberman_lobby/packets/PlayerInputsPacket.hpp"
#include "bomberman_lobby/BombermanPacket.hpp"
#include "ige.hpp"

using ige::plugin::input::InputManager;
using ige::plugin::input::InputRegistryState;
using ige::plugin::input::KeyboardKey;

PlayerInputsPacket::PlayerInputsPacket(const InputManager& manager)
{
    if (manager.keyboard().is_down(KeyboardKey::KEY_ARROW_UP)) {
        inputs.set_state(
            KeyboardKey::KEY_ARROW_UP, InputRegistryState::PRESSED);
    }

    if (manager.keyboard().is_down(KeyboardKey::KEY_ARROW_DOWN)) {
        inputs.set_state(
            KeyboardKey::KEY_ARROW_DOWN, InputRegistryState::PRESSED);
    }

    if (manager.keyboard().is_down(KeyboardKey::KEY_ARROW_RIGHT)) {
        inputs.set_state(
            KeyboardKey::KEY_ARROW_RIGHT, InputRegistryState::PRESSED);
    }

    if (manager.keyboard().is_down(KeyboardKey::KEY_ARROW_LEFT)) {
        inputs.set_state(
            KeyboardKey::KEY_ARROW_LEFT, InputRegistryState::PRESSED);
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
    if (inputs.is_down(KeyboardKey::KEY_ARROW_UP)) {
        buff.push_back(static_cast<char>(KeyboardKey::KEY_ARROW_UP));
        buff.push_back(1);
    }

    if (inputs.is_down(KeyboardKey::KEY_ARROW_DOWN)) {
        buff.push_back(static_cast<char>(KeyboardKey::KEY_ARROW_DOWN));
        buff.push_back(1);
    }

    if (inputs.is_down(KeyboardKey::KEY_ARROW_RIGHT)) {
        buff.push_back(static_cast<char>(KeyboardKey::KEY_ARROW_RIGHT));
        buff.push_back(1);
    }

    if (inputs.is_down(KeyboardKey::KEY_ARROW_LEFT)) {
        buff.push_back(static_cast<char>(KeyboardKey::KEY_ARROW_LEFT));
        buff.push_back(1);
    }
}

PlayerInputsPacket
PlayerInputsPacket::deserialize(const std::vector<char>& data)
{
    PlayerInputsPacket packet;
    int step = 0;
    KeyboardKey key;
    bool type_parsed = false;

    for (auto& val : data) {
        if (!type_parsed) {
            type_parsed = true;
            continue;
        }

        if (step == 0) {
            key = static_cast<KeyboardKey>(val);
            step = 1;
        } else if (step = 1) {
            packet.inputs.set_state(key, static_cast<InputRegistryState>(val));
            step = 0;
        }
    }
    return packet;
}
