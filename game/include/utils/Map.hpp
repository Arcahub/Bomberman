#ifndef MAPU_HPP_
#define MAPU_HPP_

#include "ige.hpp"
#include "plugin/room/RoomPlayer.hpp"

struct PlayerSpawn {
    RoomPlayerId player_id;
    glm::vec3 pos;
};

enum class MapComponentType {
    BLOCK_MUD,
    MYSTERY_BOX,
    BLOCK_STONE,
};

struct MapComponent {
    float x;
    float y;
    MapComponentType type;
};

struct MapRessources {
    std::vector<PlayerSpawn> player_spawns = {};
    std::vector<MapComponent> schema = {};
};

const glm::vec3 MAP_SPAWNS[4] = {
    glm::vec3 { 1.0f, 2.0f, 1.0f },
    glm::vec3 { 13.0f, 2.0f, 13.0f },
    glm::vec3 { 13.0f, 2.0f, 1.0f },
    glm::vec3 { 1.0f, 2.0f, 13.0f },
};

class Map {
public:
    static void InitMap(ige::ecs::World& wld);

    static std::vector<MapComponent>
    GenerateMapSchema(ige::ecs::World& wld, unsigned int seed);

    static void LoadMapContent(ige::ecs::World& wld, const MapRessources& map);

protected:
private:
};

#endif /* !MAPLOADING_HPP_ */
