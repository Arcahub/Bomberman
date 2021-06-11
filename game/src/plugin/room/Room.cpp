#include "plugin/room/Room.hpp"

RoomPlayer& Room::add_player(const RoomNetworkPlayer& player)
{
    m_players.push_back(
        { RoomPlayerType::NETWORK, m_players.size() + 1, player });
    return m_players.back();
}

RoomPlayer& Room::add_player(const RoomLocalPlayer& player)
{
    m_players.push_back(
        { RoomPlayerType::LOCAL, m_players.size() + 1, player });
    return m_players.back();
}

RoomPlayer& Room::add_player(const RoomAIPlayer& player)
{
    m_players.push_back({ RoomPlayerType::AI, m_players.size() + 1, player });
    return m_players.back();
}

void Room::remove_player(const RoomPlayer& player)
{
    m_players.erase(m_players.begin() + player.id - 1);
}

std::vector<RoomPlayer*> Room::players()
{
    std::vector<RoomPlayer*> res;

    for (auto& player : m_players) {
        res.push_back(&player);
    }
    return res;
}
