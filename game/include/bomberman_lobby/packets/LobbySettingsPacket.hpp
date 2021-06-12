#ifndef E281A5CB_50E2_40B2_AB15_17FB52AA58E6
#define E281A5CB_50E2_40B2_AB15_17FB52AA58E6

#include "bomberman_lobby/BombermanLobbySettings.hpp"
#include <vector>

class LobbySettingsPacket {
public:
    BombermanLobbySettings settings;

    std::vector<char> serialize();
    void serialize(std::vector<char>& buff);
    static LobbySettingsPacket deserialize(const std::vector<char>& data);
};

#endif /* E281A5CB_50E2_40B2_AB15_17FB52AA58E6 */
