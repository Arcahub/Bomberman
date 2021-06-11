#ifndef B837E13A_A33D_43F6_8F45_9CAD20137AB7
#define B837E13A_A33D_43F6_8F45_9CAD20137AB7

#include "Room.hpp"
#include "RoomPacket.hpp"
#include "RoomPlayer.hpp"
#include "ige.hpp"
#include "plugin/NetworkPlugin.hpp"
#include <queue>
#include <unordered_map>
#include <vector>

class RoomServer : public Room {
public:
    RoomServer(ige::ecs::World& wld, int port = -1);

    void send_room_data(const std::vector<char>& data);
    void send_player_data(
        const RoomLocalPlayer& player, const std::vector<char>& data);
    std::optional<std::vector<char>> recv_room_data();
    std::optional<std::vector<char>>
    recv_player_data(const RoomNetworkPlayer& player);

    void update(ige::ecs::World& wld);

private:
    std::queue<RoomPacket> m_room_packets;
    std::unordered_map<NetworkId, std::queue<RoomPacket>> m_players_packets;
    std::shared_ptr<Server> m_server;
};

#endif /* B837E13A_A33D_43F6_8F45_9CAD20137AB7 */
