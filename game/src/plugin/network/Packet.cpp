#include "plugin/network/Packet.hpp"

Packet::Packet()
{
}

void Packet::set_data(const std::vector<char>& data)
{
    m_data = data;
}

std::vector<char> Packet::get_data() const
{
    return m_data;
}

void Packet::is_important(bool is_important)
{
    m_important = is_important;
}

bool Packet::is_important() const
{
    return m_important;
}
