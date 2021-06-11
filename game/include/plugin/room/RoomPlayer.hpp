#ifndef D0DF6384_5F29_4A29_B943_EEA76273E25E
#define D0DF6384_5F29_4A29_B943_EEA76273E25E

#include "RoomPacket.hpp"
#include "ige.hpp"
#include "plugin/NetworkPlugin.hpp"
#include <optional>
#include <variant>
#include <vector>

enum class RoomPlayerType { NETWORK, LOCAL, AI };

class RoomNetworkPlayer {
public:
    ige::ecs::EntityId entity_id;
    NetworkId network_id;

    void handle_update_packet(ige::ecs::World& wld, const RoomPacket& packet);
};

class RoomLocalPlayer {
public:
    ige::ecs::EntityId entity_id;
    std::optional<NetworkId> network_id;

    void update(ige::ecs::World& wld);
    std::vector<char> serialize_inputs(ige::ecs::World& wld);
};

class RoomAIPlayer {
public:
    ige::ecs::EntityId entity_id;
};

typedef size_t RoomPlayerId;

struct RoomPlayer {
    RoomPlayerType type;
    RoomPlayerId id;
    std::variant<RoomNetworkPlayer, RoomLocalPlayer, RoomAIPlayer> data;
};

#endif /* D0DF6384_5F29_4A29_B943_EEA76273E25E */
