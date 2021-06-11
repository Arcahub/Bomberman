#ifndef B60B813D_3FF6_4785_A9A4_FDA50A3171E6
#define B60B813D_3FF6_4785_A9A4_FDA50A3171E6

#include "Room.hpp"
#include "RoomPacket.hpp"
#include "RoomPlayer.hpp"
#include "ige.hpp"
#include "plugin/NetworkPlugin.hpp"
#include <queue>
#include <unordered_map>
#include <vector>

class RoomClient : public Room {
public:
    RoomClient(ige::ecs::World& wld, const std::string& addr, int port);

    void send_room_data(const std::vector<char>& data);
    void send_player_data(
        const RoomLocalPlayer& player, const std::vector<char>& data);
    std::optional<std::vector<char>> recv_room_data();
    std::optional<std::vector<char>>
    recv_player_data(const RoomNetworkPlayer& player);

    void update(ige::ecs::World& wld);

private:
    // std::shared_ptr<IClient> m_client;
    std::queue<RoomPacket> m_room_packets;
    std::unordered_map<NetworkId, std::queue<RoomPacket>> m_players_packets;
};

#endif /* B60B813D_3FF6_4785_A9A4_FDA50A3171E6 */
