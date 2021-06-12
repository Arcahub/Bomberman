#ifndef B953312E_49B6_44DB_920B_A54128BE376C
#define B953312E_49B6_44DB_920B_A54128BE376C

#include "ige.hpp"
#include <vector>

class PlayerInputsPacket {
public:
    PlayerInputsPacket() = default;
    PlayerInputsPacket(const ige::plugin::input::InputManager& manager);

    ige::plugin::input::InputRegistry<ige::plugin::input::KeyboardKey> inputs;

    std::vector<char> serialize();
    void serialize(std::vector<char>& buff);
    static PlayerInputsPacket deserialize(const std::vector<char>& data);
};

#endif /* B953312E_49B6_44DB_920B_A54128BE376C */
