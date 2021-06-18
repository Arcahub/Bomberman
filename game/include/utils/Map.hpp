#ifndef MAPLOADING_HPP_
#define MAPLOADING_HPP_

#include "ige.hpp"

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
    ige::ecs::EntityId map_id;
    std::vector<ige::ecs::EntityId> mud_blocks;
    std::vector<ige::ecs::EntityId> players;
    std::vector<MapComponent> schema;
};

class Map {
public:
    static void InitMap(ige::ecs::World& wld);

    static std::vector<MapComponent>
    GenerateMapSchema(ige::ecs::World& wld, unsigned int seed);

    static void
    LoadMapContent(ige::ecs::World& wld, const std::vector<MapComponent>& map);

protected:
private:
};

#endif /* !MAPLOADING_HPP_ */
