#include "plugin/room/RoomPacket.hpp"
#include <cstddef>

std::vector<char> RoomPacket::serialize()
{
    std::vector<char> data;

    serialize(data);
    return data;
}

void RoomPacket::serialize(std::vector<char>& buff)
{
    buff.push_back(static_cast<char>(type));
    if (type == RoomPacketType::PLAYER) {
        buff.push_back((char)*player_id >> 24);
        buff.push_back((char)*player_id >> 16);
        buff.push_back((char)*player_id >> 8);
        buff.push_back((char)*player_id >> 0);
    }
    buff.push_back(m_data.size() >> 24);
    buff.push_back(m_data.size() >> 16);
    buff.push_back(m_data.size() >> 8);
    buff.push_back(m_data.size() >> 0);
    for (const auto& val : m_data) {
        buff.push_back(val);
    }
}

RoomPacket RoomPacket::deserialize(const std::vector<char>& data)
{
    RoomPacket packet;
    size_t data_len = 0;

    for (auto& val : data) {
        switch (packet.m_state) {
        case RoomPacketState::EMPTY:
            packet.type = static_cast<RoomPacketType>(val);
            if (packet.type == RoomPacketType::ROOM) {
                packet.m_state = RoomPacketState::DATA_LEN1;
            } else if (packet.type == RoomPacketType::PLAYER) {
                packet.m_state = RoomPacketState::TYPE;
            }
            break;
        case RoomPacketState::TYPE:
            packet.m_player_id = uint32_t(val) << 24;
            packet.m_state = RoomPacketState::PLAYER_ID1;
            break;
        case RoomPacketState::PLAYER_ID1:
            packet.m_player_id |= uint32_t(val) << 16;
            packet.m_state = RoomPacketState::PLAYER_ID2;
            break;
        case RoomPacketState::PLAYER_ID2:
            packet.m_player_id |= uint32_t(val) << 8;
            packet.m_state = RoomPacketState::PLAYER_ID3;
            break;
        case RoomPacketState::PLAYER_ID3:
            packet.m_player_id |= uint32_t(val) << 0;
            packet.player_id = packet.m_player_id;
            packet.m_state = RoomPacketState::DATA_LEN1;
            break;
        case RoomPacketState::DATA_LEN1:
            data_len = uint32_t(val) << 24;
            packet.m_state = RoomPacketState::DATA_LEN2;
            break;
        case RoomPacketState::DATA_LEN2:
            data_len |= uint32_t(val) << 16;
            packet.m_state = RoomPacketState::DATA_LEN3;
            break;
        case RoomPacketState::DATA_LEN3:
            data_len |= uint32_t(val) << 8;
            packet.m_state = RoomPacketState::DATA_LEN4;
            break;
        case RoomPacketState::DATA_LEN4:
            data_len |= uint32_t(val) << 0;
            packet.m_state = RoomPacketState::DATA;
            break;
        case RoomPacketState::DATA:
            if (packet.m_data.size() == data_len) {
                return packet;
            }
            packet.m_data.push_back(val);
            break;
        case RoomPacketState::COMPLETE:
            return packet;
        default:
            break;
        }
    }

    return packet;
}

bool RoomPacket::is_complete() const
{
    return m_state == RoomPacketState::COMPLETE;
}

void RoomPacket::set_data(const std::vector<char>& data)
{
    m_data = data;
}

std::vector<char> RoomPacket::get_data() const
{
    return m_data;
}
