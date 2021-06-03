#ifndef D0DF6384_5F29_4A29_B943_EEA76273E25E
#define D0DF6384_5F29_4A29_B943_EEA76273E25E

#include "RoomPacket.hpp"
#include "ige.hpp"
#include "plugin/NetworkPlugin.hpp"
#include <functional>
#include <optional>
#include <string>
#include <vector>

enum class RoomPlayerType { NETWORK, LOCAL, IA };

class RoomNetworkPlayer {
public:
    ige::ecs::EntityId entity_id;
    NetworkId network_id;

    void handle_update_packet(ige::ecs::World& wld, const RoomPacket& packet);
};

class RoomLocalPlayer {
public:
    ige::ecs::EntityId entity_id;

    void update(ige::ecs::World& wld);
    RoomPacket generate_update_packet(ige::ecs::World& wld);
};

class RoomIAPlayer {
public:
    ige::ecs::EntityId entity_id;
};

struct RoomPlayer {
    RoomPlayerType type;
    std::variant<RoomNetworkPlayer, RoomLocalPlayer, RoomIAPlayer> data;
};

#endif /* D0DF6384_5F29_4A29_B943_EEA76273E25E */