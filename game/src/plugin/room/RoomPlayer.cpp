#include "plugin/room/RoomPlayer.hpp"
#include "ige.hpp"
#include "scripts.hpp"

using ige::ecs::World;
using ige::plugin::input::InputManager;
using ige::plugin::input::InputRegistryState;
using ige::plugin::input::KeyboardKey;
using ige::plugin::script::Scripts;

void RoomNetworkPlayer::handle_update_packet(
    World& wld, const RoomPacket& packet)
{
    auto scripts = wld.get_component<Scripts>(entity_id);
    auto network_controller = scripts->get<NetworkController>();

    int step = 0;
    KeyboardKey key;
    for (auto& val : *packet.get_data()) {
        if (step == 0) {
            key = static_cast<KeyboardKey>(val);
            step = 1;
        } else if (step = 1) {
            network_controller->inputs.set_state(
                key, static_cast<InputRegistryState>(val));
            step = 0;
        }
    }
    network_controller->update();
}

RoomPacket RoomLocalPlayer::generate_update_packet(World& wld)
{
    std::deque<uint8_t> inputs;

    auto input = wld.get<InputManager>();

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_UP)) {
        inputs.push_back(static_cast<uint8_t>(KeyboardKey::KEY_ARROW_UP));
        inputs.push_back(1);
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_DOWN)) {
        inputs.push_back(static_cast<uint8_t>(KeyboardKey::KEY_ARROW_DOWN));
        inputs.push_back(1);
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_RIGHT)) {
        inputs.push_back(static_cast<uint8_t>(KeyboardKey::KEY_ARROW_RIGHT));
        inputs.push_back(1);
    }

    if (input->keyboard().is_down(KeyboardKey::KEY_ARROW_LEFT)) {
        inputs.push_back(static_cast<uint8_t>(KeyboardKey::KEY_ARROW_LEFT));
        inputs.push_back(1);
    }

    RoomPacket packet;
    packet.type = RoomPacketType::PLAYER_UPDATE;
    packet.set_data(inputs);
    return packet;
}
