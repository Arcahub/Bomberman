#ifndef A66414FA_2867_45B1_BA13_A79955AA026C
#define A66414FA_2867_45B1_BA13_A79955AA026C

#include "ige.hpp"

struct PlayerInfo {
};

class Player {
public:
    static ige::ecs::EntityId
    generate(ige::ecs::World& wld, const PlayerInfo& info);
};

#endif /* A66414FA_2867_45B1_BA13_A79955AA026C */
