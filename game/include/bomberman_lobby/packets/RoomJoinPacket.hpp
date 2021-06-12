#ifndef EA8C0597_C384_4082_85C9_034E6AABAEB0
#define EA8C0597_C384_4082_85C9_034E6AABAEB0

#include "plugin/room/RoomPlayerId.hpp"
#include <glm/vec3.hpp>
#include <vector>

class RoomJoinPacket {
public:
    struct Player {
        RoomPlayerId id;
        glm::vec3 position;
    };

    // Id of player that receiv this packet
    RoomPlayerId player_id;
    std::vector<Player> players;

    std::vector<char> serialize();
    void serialize(std::vector<char>& buff);
    static RoomJoinPacket deserialize(const std::vector<char>& data);
};

#endif /* EA8C0597_C384_4082_85C9_034E6AABAEB0 */
