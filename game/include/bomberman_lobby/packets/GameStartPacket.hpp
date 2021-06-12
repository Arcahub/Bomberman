#ifndef CB19F92E_7A8F_45D3_9CCB_55CD9C3F730D
#define CB19F92E_7A8F_45D3_9CCB_55CD9C3F730D

#include "plugin/room/RoomPlayerId.hpp"
#include <vector>

class GameStartPacket {
public:
    // Map infos
    // Players spawns

    struct MapInfos {
    };

    struct PlayerSpawn {
        RoomPlayerId player_id;
    };

    MapInfos map_infos;
    std::vector<PlayerSpawn> players_spawn;

    std::vector<char> serialize();
    void serialize(std::vector<char>& buff);
    static GameStartPacket deserialize(const std::vector<char>& data);
};

#endif /* CB19F92E_7A8F_45D3_9CCB_55CD9C3F730D */
