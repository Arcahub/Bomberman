
#include "plugin/network/Packet.hpp"
#include <cstdint>

Packet::Packet()
{
    m_state = PacketState::EMPTY;
}

void Packet::set_data(const std::deque<uint8_t>& data)
{
    m_data = data;
}

std::optional<std::deque<uint8_t>> Packet::get_data() const
{
    if (m_state == PacketState::COMPLETE) {
        return m_data;
    }
    return {};
}

std::deque<uint8_t> Packet::serialize() const
{
    std::deque<uint8_t> data;

    data.push_back(0xBC);
    u_int32_t len = m_data.size();
    data.push_back(len >> 24);
    data.push_back(len >> 16);
    data.push_back(len >> 8);
    data.push_back(len >> 0);
    for (auto& val : m_data) {
        data.push_back(val);
    }
    return data;
}

void Packet::serialize(std::deque<uint8_t>& buff) const
{
    buff.push_back(0xBC);

    u_int32_t len = m_data.size();
    buff.push_back(len >> 24);
    buff.push_back(len >> 16);
    buff.push_back(len >> 8);
    buff.push_back(len >> 0);
    for (auto& val : m_data) {
        buff.push_back(val);
    }
}

bool Packet::deserialize(const std::deque<uint8_t>& data, size_t& bytes_read)
{
    for (auto& val : data) {
        bytes_read++;
        switch (m_state) {
        case PacketState::EMPTY:
            if (val == 0xBC) {
                m_state = PacketState::HEADER_VALIDATED;
            }
            break;
        case PacketState::HEADER_VALIDATED:
            m_data_len = u_int32_t(val) << 24;
            m_state = PacketState::SIZE_1;
            break;
        case PacketState::SIZE_1:
            m_data_len |= u_int32_t(val) << 16;
            m_state = PacketState::SIZE_2;
            break;
        case PacketState::SIZE_2:
            m_data_len |= u_int32_t(val) << 8;
            m_state = PacketState::SIZE_3;
            break;
        case PacketState::SIZE_3:
            m_data_len |= u_int32_t(val) << 0;
            m_state = PacketState::SIZE_4;
            break;
        case PacketState::SIZE_4:
            if (m_data_len == m_data.size()) {
                m_state = PacketState::COMPLETE;
            }
            m_data.push_back(val);
            break;
        case PacketState::COMPLETE:
            return true;
        default:
            break;
        }
    }
    if (m_data_len == m_data.size()) {
        m_state = PacketState::COMPLETE;
    }
    return m_state == PacketState::COMPLETE;
}

bool Packet::is_complete() const
{
    return PacketState::COMPLETE == m_state;
}
