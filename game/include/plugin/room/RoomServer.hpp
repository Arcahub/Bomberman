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
    RoomServer(int port = -1);

    void send_room_data(const std::vector<char>& data);
    void send_room_data(const std::vector<char>& data, const RoomPlayer& dest);
    void send_room_data(const std::vector<char>& data, const NetworkId& dest);
    void
    send_player_data(const RoomPlayer& player, const std::vector<char>& data);
    void send_player_data(
        const RoomPlayer& player, const std::vector<char>& data,
        const RoomPlayer& dest);
    void send_player_data(
        const RoomPlayer& player, const std::vector<char>& data,
        const NetworkId& dest);
    bool is_connected(const RoomPlayer& player);

    std::optional<RoomPacket> recv();

    void update();

private:
    std::queue<RoomPacket> m_packets;
    std::unordered_map<RoomPlayerId, NetworkId> m_players_network_id;
    Server m_server;
};

#endif /* B837E13A_A33D_43F6_8F45_9CAD20137AB7 */
