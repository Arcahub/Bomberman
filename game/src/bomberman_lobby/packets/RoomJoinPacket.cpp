#include "bomberman_lobby/packets/RoomJoinPacket.hpp"
#include "bomberman_lobby/BombermanPacket.hpp"

std::vector<char> RoomJoinPacket::serialize()
{
    std::vector<char> data;

    serialize(data);
    return data;
}

void RoomJoinPacket::serialize(std::vector<char>& buff)
{
    buff.push_back(
        static_cast<char>(BombermanPacketType::ROOM_SETTINGS_UPDATE));
    // TO-DO
}

RoomJoinPacket RoomJoinPacket::deserialize(const std::vector<char>& data)
{
    RoomJoinPacket packet;
    bool type_parsed = false;

    for (auto& val : data) {
        if (!type_parsed) {
            type_parsed = true;
            continue;
        }
    }

    return packet;
}
