#include "plugin/room/Room.hpp"

void Room::add_player(const RoomPlayer& player)
{
    m_players.push_back(player);
}

void Room::remove_player(const RoomPlayer& player)
{
}

std::vector<RoomPlayer*> Room::players()
{
    std::vector<RoomPlayer*> res;

    for (auto& player : m_players) {
        res.push_back(&player);
    }
    return res;
}
