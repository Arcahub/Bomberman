#include "plugin/network/NetworkId.hpp"
#include <stddef.h>

size_t NetworkId::m_max_id = 0;

NetworkId NetworkId::generate()
{
    NetworkId id;

    id.m_id = NetworkId::m_max_id;
    NetworkId::m_max_id += 1;
    return id;
}

bool NetworkId::operator==(const NetworkId& id) const
{
    return id.m_id == m_id;
}
