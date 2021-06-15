#include "bomberman_lobby/packets/RoomClosePacket.hpp"
#include "bomberman_lobby/BombermanPacket.hpp"

std::vector<char> RoomClosePacket::serialize()
{
    std::vector<char> data;

    serialize(data);
    return data;
}

void RoomClosePacket::serialize(std::vector<char>& buff)
{
    buff.push_back(static_cast<char>(BombermanPacketType::ROOM_CLOSE));
}

RoomClosePacket RoomClosePacket::deserialize(const std::vector<char>& data)
{
    RoomClosePacket packet;
    bool type_parsed = false;

    for (auto& val : data) {
        if (!type_parsed) {
            type_parsed = true;
            continue;
        }
    }

    return packet;
}
