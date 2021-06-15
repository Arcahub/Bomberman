#include "bomberman_lobby/packets/PlayerJoinPacket.hpp"
#include "bomberman_lobby/BombermanPacket.hpp"

std::vector<char> PlayerJoinPacket::serialize()
{
    std::vector<char> data;

    serialize(data);
    return data;
}

void PlayerJoinPacket::serialize(std::vector<char>& buff)
{
    buff.push_back(static_cast<char>(BombermanPacketType::PLAYER_JOIN));
}

PlayerJoinPacket PlayerJoinPacket::deserialize(const std::vector<char>& data)
{
    PlayerJoinPacket packet;
    bool type_parsed = false;

    for (auto& val : data) {
        if (!type_parsed) {
            type_parsed = true;
            continue;
        }
    }

    return packet;
}
