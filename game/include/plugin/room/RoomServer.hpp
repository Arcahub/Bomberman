#ifndef B837E13A_A33D_43F6_8F45_9CAD20137AB7
#define B837E13A_A33D_43F6_8F45_9CAD20137AB7

#include "RoomPacket.hpp"
#include "RoomPlayer.hpp"
#include "ige.hpp"
#include "plugin/NetworkPlugin.hpp"

class RoomServer {
public:
    RoomServer(ige::ecs::World& wld, int port = -1);

    void add_player(const RoomPlayer& player);
    void remove_player(const RoomPlayer& player);
    void update(ige::ecs::World& wld);

private:
    void handle_new_player(World& wld, IClient* client);
    RoomNetworkPlayer* find_player(const NetworkId& id);
    void player_update(World& wld, const RoomPlayer& player);

    std::vector<RoomPlayer> m_players;
    NetworkId m_id;
};

#endif /* B837E13A_A33D_43F6_8F45_9CAD20137AB7 */
