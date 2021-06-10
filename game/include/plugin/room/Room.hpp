#ifndef E9471D61_1D02_4EDA_A8EC_68E424D5F16F
#define E9471D61_1D02_4EDA_A8EC_68E424D5F16F

#include "RoomPlayer.hpp"
#include <deque>
#include <vector>

class Room {
public:
    virtual ~Room() = default;

    void add_player(const RoomPlayer& player);
    void remove_player(const RoomPlayer& player);
    std::vector<RoomPlayer*> players();

    virtual void send_room_data(const std::deque<uint8_t>& data) = 0;
    virtual void send_player_data(
        const RoomLocalPlayer& player, const std::deque<uint8_t>& data)
        = 0;
    virtual std::optional<std::deque<uint8_t>> recv_room_data() = 0;
    virtual std::optional<std::deque<uint8_t>>
    recv_player_data(const RoomNetworkPlayer& player) = 0;

protected:
    std::vector<RoomPlayer> m_players;
};

#endif /* E9471D61_1D02_4EDA_A8EC_68E424D5F16F */
