#include "bomberman_lobby/packets/GameStartPacket.hpp"
#include "bomberman_lobby/BombermanPacket.hpp"
#include "plugin/network/NetworkUtils.hpp"

std::vector<char> GameStartPacket::serialize()
{
    std::vector<char> data;

    serialize(data);
    return data;
}

void GameStartPacket::serialize(std::vector<char>& buff)
{
    buff.push_back(static_cast<char>(BombermanPacketType::GAME_START));
    buff.push_back(map_infos.map.size() >> 24);
    buff.push_back(map_infos.map.size() >> 16);
    buff.push_back(map_infos.map.size() >> 8);
    buff.push_back(map_infos.map.size() >> 0);
    for (const auto& component : map_infos.map) {
        buff.push_back(static_cast<char>(component.type));
        auto x_buff = NetworkUtils::get_bytes(
            *reinterpret_cast<const unsigned int*>(&component.x));
        for (auto& val : x_buff) {
            buff.push_back(val);
        }
        auto y_buff = NetworkUtils::get_bytes(
            *reinterpret_cast<const unsigned int*>(&component.y));
        for (auto& val : y_buff) {
            buff.push_back(val);
        }
    }
    for (auto& pl : players_spawn) {
        buff.push_back(pl.player_id);
        auto x_buff = NetworkUtils::get_bytes(
            *reinterpret_cast<unsigned int*>(&pl.pos.x));
        for (auto& val : x_buff) {
            buff.push_back(val);
        }
        auto y_buff = NetworkUtils::get_bytes(
            *reinterpret_cast<unsigned int*>(&pl.pos.y));
        for (auto& val : y_buff) {
            buff.push_back(val);
        }
        auto z_buff = NetworkUtils::get_bytes(
            *reinterpret_cast<unsigned int*>(&pl.pos.z));
        for (auto& val : z_buff) {
            buff.push_back(val);
        }
    }
}

GameStartPacket GameStartPacket::deserialize(const std::vector<char>& data)
{
    GameStartPacket packet;
    State state = State::TYPE;
    size_t component_count = 0;
    MapComponent tmp_component;
    std::vector<char> float_buff;
    PlayerSpawn tmp_spawn;

    for (auto& val : data) {
        switch (state) {
        case State::TYPE:
            state = State::COMPONENT_COUNT1;
            break;
        case State::COMPONENT_COUNT1:
            component_count = uint32_t(val) << 24;
            state = State::COMPONENT_COUNT2;
            break;
        case State::COMPONENT_COUNT2:
            component_count |= uint32_t(val) << 16;
            state = State::COMPONENT_COUNT3;
            break;
        case State::COMPONENT_COUNT3:
            component_count |= uint32_t(val) << 8;
            state = State::COMPONENT_COUNT4;
            break;
        case State::COMPONENT_COUNT4:
            component_count |= uint32_t(val) << 0;
            state = State::COMPONENT_TYPE;
            break;
        case State::COMPONENT_TYPE:
            tmp_component.type = static_cast<MapComponentType>(val);
            state = State::COMPONENT_X1;
            break;
        case State::COMPONENT_X1:
            float_buff.push_back(val);
            state = State::COMPONENT_X2;
            break;

        case State::COMPONENT_X2:
            float_buff.push_back(val);
            state = State::COMPONENT_X3;
            break;

        case State::COMPONENT_X3:
            float_buff.push_back(val);
            state = State::COMPONENT_X4;
            break;

        case State::COMPONENT_X4:
            float_buff.push_back(val);
            tmp_component.x = NetworkUtils::get<float>(float_buff);
            state = State::COMPONENT_Y1;
            break;

        case State::COMPONENT_Y1:
            float_buff.push_back(val);
            state = State::COMPONENT_Y2;
            break;

        case State::COMPONENT_Y2:
            float_buff.push_back(val);
            state = State::COMPONENT_Y3;
            break;

        case State::COMPONENT_Y3:
            float_buff.push_back(val);
            state = State::COMPONENT_Y4;
            break;

        case State::COMPONENT_Y4:
            float_buff.push_back(val);
            tmp_component.y = NetworkUtils::get<float>(float_buff);
            packet.map_infos.map.push_back(tmp_component);
            if (packet.map_infos.map.size() == component_count) {
                state = State::PLAYER_SPAWN_PLAYER_ID;
            } else {
                state = State::COMPONENT_TYPE;
            }
            break;
        case State::PLAYER_SPAWN_PLAYER_ID:
            tmp_spawn.player_id = val;
            state = State::PLAYER_SPAWN_POS_X1;
            break;

        case State::PLAYER_SPAWN_POS_X1:
            float_buff.push_back(val);
            state = State::PLAYER_SPAWN_POS_X2;
            break;

        case State::PLAYER_SPAWN_POS_X2:
            float_buff.push_back(val);
            state = State::PLAYER_SPAWN_POS_X3;
            break;

        case State::PLAYER_SPAWN_POS_X3:
            float_buff.push_back(val);
            state = State::PLAYER_SPAWN_POS_X4;
            break;

        case State::PLAYER_SPAWN_POS_X4:
            float_buff.push_back(val);
            tmp_spawn.pos.x = NetworkUtils::get<float>(float_buff);
            state = State::PLAYER_SPAWN_POS_Y1;
            break;

        case State::PLAYER_SPAWN_POS_Y1:
            float_buff.push_back(val);
            state = State::PLAYER_SPAWN_POS_Y2;
            break;

        case State::PLAYER_SPAWN_POS_Y2:
            float_buff.push_back(val);
            state = State::PLAYER_SPAWN_POS_Y3;
            break;

        case State::PLAYER_SPAWN_POS_Y3:
            float_buff.push_back(val);
            state = State::PLAYER_SPAWN_POS_Y4;
            break;

        case State::PLAYER_SPAWN_POS_Y4:
            float_buff.push_back(val);
            tmp_spawn.pos.y = NetworkUtils::get<float>(float_buff);
            state = State::PLAYER_SPAWN_POS_Z1;
            break;

        case State::PLAYER_SPAWN_POS_Z1:
            float_buff.push_back(val);
            state = State::PLAYER_SPAWN_POS_Z2;
            break;

        case State::PLAYER_SPAWN_POS_Z2:
            float_buff.push_back(val);
            state = State::PLAYER_SPAWN_POS_Z3;
            break;

        case State::PLAYER_SPAWN_POS_Z3:
            float_buff.push_back(val);
            state = State::PLAYER_SPAWN_POS_Z4;
            break;

        case State::PLAYER_SPAWN_POS_Z4:
            float_buff.push_back(val);
            tmp_spawn.pos.z = NetworkUtils::get<float>(float_buff);
            packet.players_spawn.push_back(tmp_spawn);
            state = State::PLAYER_SPAWN_PLAYER_ID;
            break;
        default:
            break;
        }
    }

    return packet;
}
