#ifndef B953312E_49B6_44DB_920B_A54128BE376C
#define B953312E_49B6_44DB_920B_A54128BE376C

#include "ige.hpp"
#include "scripts/NetworkController.hpp"
#include <vector>

class PlayerInputsPacket {
public:
    PlayerInputsPacket() = default;
    PlayerInputsPacket(const ige::plugin::input::InputManager& manager);

    std::vector<NetworkController::Actions> actions;

    std::vector<char> serialize();
    void serialize(std::vector<char>& buff);
    static PlayerInputsPacket deserialize(const std::vector<char>& data);
};

#endif /* B953312E_49B6_44DB_920B_A54128BE376C */
