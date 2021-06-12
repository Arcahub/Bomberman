#ifndef D0DF6384_5F29_4A29_B943_EEA76273E25E
#define D0DF6384_5F29_4A29_B943_EEA76273E25E

#include "RoomPacket.hpp"
#include "RoomPlayerId.hpp"
#include "ige.hpp"
#include "plugin/NetworkPlugin.hpp"
#include <optional>
#include <variant>
#include <vector>

enum class RoomPlayerType { NETWORK, LOCAL, AI };

struct RoomPlayer {
    RoomPlayerType type;
    RoomPlayerId id;
    ige::ecs::EntityId entity_id;
};

#endif /* D0DF6384_5F29_4A29_B943_EEA76273E25E */
