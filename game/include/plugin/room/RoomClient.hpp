#ifndef B60B813D_3FF6_4785_A9A4_FDA50A3171E6
#define B60B813D_3FF6_4785_A9A4_FDA50A3171E6

#include "Room.hpp"
#include "RoomPacket.hpp"
#include "RoomPlayer.hpp"
#include "ige.hpp"
#include "plugin/network/Client.hpp"
#include <queue>
#include <unordered_map>
#include <vector>

class RoomClient : public Room {
public:
    RoomClient(const std::string& addr, int port);

    void send_room_data(const std::vector<char>& data);
    void
    send_player_data(const RoomPlayer& player, const std::vector<char>& data);
    std::optional<RoomPacket> recv();

    void update();

private:
    std::unique_ptr<Client> m_client;
    std::queue<RoomPacket> m_packets;
    std::unordered_map<NetworkId, std::queue<RoomPacket>> m_players_packets;
};

#endif /* B60B813D_3FF6_4785_A9A4_FDA50A3171E6 */
