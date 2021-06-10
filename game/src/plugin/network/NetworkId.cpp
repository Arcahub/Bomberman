#include "plugin/network/NetworkId.hpp"
#include <stddef.h>

size_t NetworkId::m_max_id = 0;

NetworkId::NetworkId()
{
}

NetworkId::NetworkId(size_t id)
{
    m_id = id;
    if (NetworkId::m_max_id < m_id + 1)
        NetworkId::m_max_id = m_id + 1;
}

NetworkId::NetworkId(const NetworkId& other)
{
    *this = other;
}

NetworkId::NetworkId(NetworkId&& other)
{
    *this = other;
}

NetworkId NetworkId::generate()
{
    NetworkId id;

    id.m_id = NetworkId::m_max_id;
    NetworkId::m_max_id += 1;
    return id;
}

NetworkId& NetworkId::operator=(const NetworkId& rhs)
{
    m_id = rhs.m_id;
    if (NetworkId::m_max_id < m_id + 1)
        NetworkId::m_max_id = m_id + 1;
    return *this;
}

NetworkId& NetworkId::operator=(NetworkId&& rhs)
{
    m_id = rhs.m_id;
    if (NetworkId::m_max_id < m_id + 1)
        NetworkId::m_max_id = m_id + 1;
    return *this;
}

bool NetworkId::operator==(const NetworkId& id) const
{
    return id.m_id == m_id;
}

size_t NetworkId::value() const
{
    return m_id;
}
