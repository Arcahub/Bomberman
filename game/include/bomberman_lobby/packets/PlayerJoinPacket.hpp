#ifndef B886D307_D144_43EC_82C6_D077D68F93B0
#define B886D307_D144_43EC_82C6_D077D68F93B0

#include "plugin/room/RoomPlayerId.hpp"
#include <glm/vec3.hpp>
#include <vector>

class PlayerJoinPacket {
public:
    std::vector<char> serialize();
    void serialize(std::vector<char>& buff);
    static PlayerJoinPacket deserialize(const std::vector<char>& data);
};

#endif /* B886D307_D144_43EC_82C6_D077D68F93B0 */
