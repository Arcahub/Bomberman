#ifndef CB19F92E_7A8F_45D3_9CCB_55CD9C3F730D
#define CB19F92E_7A8F_45D3_9CCB_55CD9C3F730D

#include "plugin/room/RoomPlayerId.hpp"
#include "utils/Map.hpp"
#include <vector>

class GameStartPacket {
public:
    // Map infos
    // Players spawns

    struct MapInfos {
        std::vector<MapComponent> map;
    };

    MapInfos map_infos;
    std::vector<PlayerSpawn> players_spawn;

    std::vector<char> serialize();
    void serialize(std::vector<char>& buff);
    static GameStartPacket deserialize(const std::vector<char>& data);

private:
    enum class State {
        TYPE,
        COMPONENT_COUNT1,
        COMPONENT_COUNT2,
        COMPONENT_COUNT3,
        COMPONENT_COUNT4,
        COMPONENT_TYPE,
        COMPONENT_X1,
        COMPONENT_X2,
        COMPONENT_X3,
        COMPONENT_X4,
        COMPONENT_Y1,
        COMPONENT_Y2,
        COMPONENT_Y3,
        COMPONENT_Y4,
        PLAYER_SPAWN_PLAYER_ID,
        PLAYER_SPAWN_POS_X1,
        PLAYER_SPAWN_POS_X2,
        PLAYER_SPAWN_POS_X3,
        PLAYER_SPAWN_POS_X4,
        PLAYER_SPAWN_POS_Y1,
        PLAYER_SPAWN_POS_Y2,
        PLAYER_SPAWN_POS_Y3,
        PLAYER_SPAWN_POS_Y4,
        PLAYER_SPAWN_POS_Z1,
        PLAYER_SPAWN_POS_Z2,
        PLAYER_SPAWN_POS_Z3,
        PLAYER_SPAWN_POS_Z4,
    };
};

#endif /* CB19F92E_7A8F_45D3_9CCB_55CD9C3F730D */
