#ifndef E8DFC17D_4A40_45A9_B62C_4DA3291DE24C
#define E8DFC17D_4A40_45A9_B62C_4DA3291DE24C

#include "plugin/room/RoomPlayerId.hpp"
#include <glm/vec3.hpp>
#include <vector>

class PlayerLeavePacket {
public:
    RoomPlayerId player_id;

    std::vector<char> serialize();
    void serialize(std::vector<char>& buff);
    static PlayerLeavePacket deserialize(const std::vector<char>& data);
};

#endif /* E8DFC17D_4A40_45A9_B62C_4DA3291DE24C */
