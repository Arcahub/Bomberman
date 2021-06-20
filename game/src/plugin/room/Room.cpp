#include "plugin/room/Room.hpp"
#include "ige.hpp"

using ige::ecs::EntityId;

RoomPlayer&
Room::add_player(const RoomPlayerType& type, const EntityId& entity_id)
{
    return add_player(type, m_players.size() + 1, entity_id);
}

RoomPlayer& Room::add_player(
    const RoomPlayerType& type, const RoomPlayerId& id,
    const EntityId& entity_id)
{
    m_players.push_back({ type, id, entity_id });
    return m_players.back();
}

void Room::remove_player(const RoomPlayer& player)
{
    m_players.erase(
        std::remove_if(
            m_players.begin(), m_players.end(),
            [&](const RoomPlayer& p) { return player.id == p.id; }),
        m_players.end());
}

std::vector<RoomPlayer*> Room::players()
{
    std::vector<RoomPlayer*> res;

    for (auto& player : m_players) {
        res.push_back(&player);
    }
    return res;
}

RoomPlayer* Room::player(const RoomPlayerId& id)
{
    for (auto& player : m_players) {
        if (player.id == id)
            return &player;
    }
    return nullptr;
}
