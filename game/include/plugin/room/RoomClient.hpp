#ifndef B60B813D_3FF6_4785_A9A4_FDA50A3171E6
#define B60B813D_3FF6_4785_A9A4_FDA50A3171E6

#include "RoomPacket.hpp"
#include "RoomPlayer.hpp"
#include "ige.hpp"
#include "plugin/NetworkPlugin.hpp"

class RoomClient {
public:
    RoomClient(ige::ecs::World& wld, const std::string& addr, int port);

    void add_player(ige::ecs::World& wld);

    void update(ige::ecs::World& wld);

private:
    RoomNetworkPlayer* find_player(const NetworkId& id);

    void
    handle_room_join_packet(ige::ecs::World& wld, const RoomPacket& packet);
    void
    handle_player_join_packet(ige::ecs::World& wld, const RoomPacket& packet);

    std::vector<RoomPlayer> m_players;
    NetworkId m_network_id;
    std::optional<ige::ecs::EntityId> m_entity_id;
};

#endif /* B60B813D_3FF6_4785_A9A4_FDA50A3171E6 */
