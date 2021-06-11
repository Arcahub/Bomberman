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
        m_data.push_back((char)netword_id->value() >> 24);
        m_data.push_back((char)netword_id->value() >> 16);
        m_data.push_back((char)netword_id->value() >> 8);
        m_data.push_back((char)netword_id->value() >> 0);
    }
}

bool RoomPacket::deserialize(const std::vector<char>& data)
{
    for (auto& val : data) {
        switch (m_state) {
        case RoomPacketState::EMPTY:
            type = static_cast<RoomPacketType>(val);
            if (type == RoomPacketType::ROOM) {
                m_state = RoomPacketState::COMPLETE;
            } else if (type == RoomPacketType::PLAYER) {
                m_state = RoomPacketState::TYPE;
            }
            break;
        case RoomPacketState::TYPE:
            m_network_id = uint32_t(val) << 24;
            m_state = RoomPacketState::PLAYER_ID1;
            break;
        case RoomPacketState::PLAYER_ID1:
            m_network_id |= uint32_t(val) << 16;
            m_state = RoomPacketState::PLAYER_ID2;
            break;
        case RoomPacketState::PLAYER_ID2:
            m_network_id |= uint32_t(val) << 8;
            m_state = RoomPacketState::PLAYER_ID3;
            break;
        case RoomPacketState::PLAYER_ID3:
            m_network_id |= uint32_t(val) << 0;
            netword_id = m_network_id;
            m_state = RoomPacketState::COMPLETE;
            break;
        case RoomPacketState::COMPLETE:
            return true;
        default:
            break;
        }
    }

    return m_state == RoomPacketState::COMPLETE;
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
