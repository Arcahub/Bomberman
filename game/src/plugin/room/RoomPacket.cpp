#include "plugin/room/RoomPacket.hpp"
#include <cstddef>

std::deque<uint8_t> RoomPacket::serialize()
{
    std::deque<uint8_t> data;

    if (type == RoomPacketType::PLAYER) {
        m_data.push_front((uint8_t)netword_id->value() >> 0);
        m_data.push_front((uint8_t)netword_id->value() >> 8);
        m_data.push_front((uint8_t)netword_id->value() >> 16);
        m_data.push_front((uint8_t)netword_id->value() >> 24);
    }
    m_data.push_front(static_cast<uint8_t>(type));
    Packet::serialize(data);
    return data;
}

void RoomPacket::serialize(std::deque<uint8_t>& buff)
{
    if (type == RoomPacketType::PLAYER) {
        m_data.push_front((uint8_t)netword_id->value() >> 0);
        m_data.push_front((uint8_t)netword_id->value() >> 8);
        m_data.push_front((uint8_t)netword_id->value() >> 16);
        m_data.push_front((uint8_t)netword_id->value() >> 24);
    }
    m_data.push_front(static_cast<uint8_t>(type));
    Packet::serialize(buff);
}

bool RoomPacket::deserialize(
    const std::deque<uint8_t>& data, size_t& bytes_read)
{
    for (auto& val : data) {
        bytes_read++;
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
