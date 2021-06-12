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
    m_data.push_back(static_cast<char>(type));
    if (type == RoomPacketType::PLAYER) {
        m_data.push_back((char)*player_id >> 24);
        m_data.push_back((char)*player_id >> 16);
        m_data.push_back((char)*player_id >> 8);
        m_data.push_back((char)*player_id >> 0);
    }
}

RoomPacket RoomPacket::deserialize(const std::vector<char>& data)
{
    RoomPacket packet;
    for (auto& val : data) {
        switch (packet.m_state) {
        case RoomPacketState::EMPTY:
            packet.type = static_cast<RoomPacketType>(val);
            if (packet.type == RoomPacketType::ROOM) {
                packet.m_state = RoomPacketState::COMPLETE;
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
            packet.m_state = RoomPacketState::COMPLETE;
            return packet;
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

std::optional<std::vector<char>> RoomPacket::get_data() const
{
    if (m_state == RoomPacketState::COMPLETE) {
        return {};
    }
    return m_data;
}
