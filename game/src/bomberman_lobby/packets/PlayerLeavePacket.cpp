#include "bomberman_lobby/packets/PlayerLeavePacket.hpp"
#include "bomberman_lobby/BombermanPacket.hpp"

std::vector<char> PlayerLeavePacket::serialize()
{
    std::vector<char> data;

    serialize(data);
    return data;
}

void PlayerLeavePacket::serialize(std::vector<char>& buff)
{
    buff.push_back(static_cast<char>(BombermanPacketType::PLAYER_LEAVE));
}

PlayerLeavePacket PlayerLeavePacket::deserialize(const std::vector<char>& data)
{
    PlayerLeavePacket packet = { 0 };
    bool type_parsed = false;

    for (auto& val : data) {
        if (!type_parsed) {
            type_parsed = true;
            continue;
        }
    }

    return packet;
}
