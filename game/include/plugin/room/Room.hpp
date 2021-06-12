#ifndef E9471D61_1D02_4EDA_A8EC_68E424D5F16F
#define E9471D61_1D02_4EDA_A8EC_68E424D5F16F

#include "RoomPlayer.hpp"
#include "ige.hpp"
#include <cstddef>
#include <vector>

class Room {
public:
    virtual ~Room() = default;

    RoomPlayer&
    add_player(const RoomPlayerType& type, const ige::ecs::EntityId& entity_id);
    RoomPlayer& add_player(
        const RoomPlayerType& type, const RoomPlayerId& id,
        const ige::ecs::EntityId& entity_id);
    void remove_player(const RoomPlayer& player);
    std::vector<RoomPlayer*> players();

    RoomPlayer* player(const RoomPlayerId& id);

    virtual void send_room_data(const std::vector<char>& data) = 0;
    virtual void
    send_player_data(const RoomPlayer& player, const std::vector<char>& data)
        = 0;
    virtual std::optional<RoomPacket> recv() = 0;

protected:
    std::vector<RoomPlayer> m_players;
};

#endif /* E9471D61_1D02_4EDA_A8EC_68E424D5F16F */
