#include "bomberman_lobby/packets/LobbySettingsPacket.hpp"
#include "bomberman_lobby/BombermanPacket.hpp"

std::vector<char> LobbySettingsPacket::serialize()
{
    std::vector<char> data;

    serialize(data);
    return data;
}

void LobbySettingsPacket::serialize(std::vector<char>& buff)
{
    buff.push_back(
        static_cast<char>(BombermanPacketType::ROOM_SETTINGS_UPDATE));
    // TO-DO
}

LobbySettingsPacket
LobbySettingsPacket::deserialize(const std::vector<char>& data)
{
    LobbySettingsPacket packet;
    bool type_parsed = false;

    for (auto& val : data) {
        if (!type_parsed) {
            type_parsed = true;
            continue;
        }
    }
    return packet;
}
