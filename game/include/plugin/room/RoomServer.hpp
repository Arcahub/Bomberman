#ifndef B837E13A_A33D_43F6_8F45_9CAD20137AB7
#define B837E13A_A33D_43F6_8F45_9CAD20137AB7

#include "Room.hpp"
#include "RoomPacket.hpp"
#include "RoomPlayer.hpp"
#include "ige.hpp"
#include "plugin/NetworkPlugin.hpp"
#include <queue>
#include <unordered_map>

class RoomServer : public Room {
public:
    RoomServer(ige::ecs::World& wld, int port = -1);

    void send_room_data(const std::deque<uint8_t>& data);
    void send_player_data(
        const RoomLocalPlayer& player, const std::deque<uint8_t>& data);
    std::optional<std::deque<uint8_t>> recv_room_data();
    std::optional<std::deque<uint8_t>>
    recv_player_data(const RoomNetworkPlayer& player);

    void update(ige::ecs::World& wld);

private:
    std::queue<RoomPacket> m_room_packets;
    std::unordered_map<NetworkId, std::queue<RoomPacket>> m_players_packets;
    std::shared_ptr<IServer> m_server;
};

#endif /* B837E13A_A33D_43F6_8F45_9CAD20137AB7 */
