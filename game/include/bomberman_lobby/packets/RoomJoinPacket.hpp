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

private:
    enum class State {
        PLAYER_ID,
        PLAYERS_COUNT,
        PLAYERS_ID,
        PLAYERS_POS_X1,
        PLAYERS_POS_X2,
        PLAYERS_POS_X3,
        PLAYERS_POS_X4,
        PLAYERS_POS_Y1,
        PLAYERS_POS_Y2,
        PLAYERS_POS_Y3,
        PLAYERS_POS_Y4,
        PLAYERS_POS_Z1,
        PLAYERS_POS_Z2,
        PLAYERS_POS_Z3,
        PLAYERS_POS_Z4,

    };
};

#endif /* EA8C0597_C384_4082_85C9_034E6AABAEB0 */
