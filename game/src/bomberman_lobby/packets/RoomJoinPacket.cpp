#include "bomberman_lobby/packets/RoomJoinPacket.hpp"
#include "bomberman_lobby/BombermanPacket.hpp"
#include "plugin/network/NetworkUtils.hpp"

std::vector<char> RoomJoinPacket::serialize()
{
    std::vector<char> data;

    serialize(data);
    return data;
}

void RoomJoinPacket::serialize(std::vector<char>& buff)
{
    buff.push_back(static_cast<char>(BombermanPacketType::ROOM_JOIN));
    buff.push_back(player_id);
    buff.push_back(players.size());
    for (auto& pl : players) {
        buff.push_back(pl.id);
        auto x_buff = NetworkUtils::get_bytes(
            *reinterpret_cast<unsigned int*>(&pl.position.x));
        for (auto& val : x_buff) {
            buff.push_back(val);
        }
        auto y_buff = NetworkUtils::get_bytes(
            *reinterpret_cast<unsigned int*>(&pl.position.y));
        for (auto& val : y_buff) {
            buff.push_back(val);
        }
        auto z_buff = NetworkUtils::get_bytes(
            *reinterpret_cast<unsigned int*>(&pl.position.z));
        for (auto& val : z_buff) {
            buff.push_back(val);
        }
    }
}

RoomJoinPacket RoomJoinPacket::deserialize(const std::vector<char>& data)
{
    RoomJoinPacket packet;
    bool type_parsed = false;
    State state = State::PLAYER_ID;
    char player_count = 0;
    Player tmp_player;
    std::vector<char> float_buff;

    for (auto& val : data) {
        if (!type_parsed) {
            type_parsed = true;
            continue;
        }
        switch (state) {
        case State::PLAYER_ID:
            packet.player_id = val;
            state = State::PLAYERS_COUNT;
            break;

        case State::PLAYERS_COUNT:
            player_count = val;
            state = State::PLAYERS_ID;
            break;

        case State::PLAYERS_ID:
            if (packet.players.size() == player_count) {
                return packet;
            }
            tmp_player.id = val;
            state = State::PLAYERS_POS_X1;
            break;

        case State::PLAYERS_POS_X1:
            float_buff.push_back(val);
            state = State::PLAYERS_POS_X2;
            break;

        case State::PLAYERS_POS_X2:
            float_buff.push_back(val);
            state = State::PLAYERS_POS_X3;
            break;

        case State::PLAYERS_POS_X3:
            float_buff.push_back(val);
            state = State::PLAYERS_POS_X4;
            break;

        case State::PLAYERS_POS_X4:
            float_buff.push_back(val);
            tmp_player.position.x = NetworkUtils::get<float>(float_buff);
            state = State::PLAYERS_POS_Y1;
            break;

        case State::PLAYERS_POS_Y1:
            float_buff.push_back(val);
            state = State::PLAYERS_POS_Y2;
            break;

        case State::PLAYERS_POS_Y2:
            float_buff.push_back(val);
            state = State::PLAYERS_POS_Y3;
            break;

        case State::PLAYERS_POS_Y3:
            float_buff.push_back(val);
            state = State::PLAYERS_POS_Y4;
            break;

        case State::PLAYERS_POS_Y4:
            float_buff.push_back(val);
            tmp_player.position.y = NetworkUtils::get<float>(float_buff);
            state = State::PLAYERS_POS_Z1;
            break;

        case State::PLAYERS_POS_Z1:
            float_buff.push_back(val);
            state = State::PLAYERS_POS_Z2;
            break;

        case State::PLAYERS_POS_Z2:
            float_buff.push_back(val);
            state = State::PLAYERS_POS_Z3;
            break;

        case State::PLAYERS_POS_Z3:
            float_buff.push_back(val);
            state = State::PLAYERS_POS_Z4;
            break;

        case State::PLAYERS_POS_Z4:
            float_buff.push_back(val);
            tmp_player.position.z = NetworkUtils::get<float>(float_buff);
            packet.players.push_back(tmp_player);
            state = State::PLAYERS_ID;
            break;
        }
    }

    return packet;
}
