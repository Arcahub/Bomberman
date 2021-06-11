#ifndef DB85CE1D_3BFD_40F8_9FB9_6AF477298A68
#define DB85CE1D_3BFD_40F8_9FB9_6AF477298A68

#include "plugin/room/RoomPacket.hpp"
#include <deque>

class BombermanPlayerPacket {
public:
    std::deque<char> serialize();
    bool deserialize(const std::deque<char>& data);
};

#endif /* DB85CE1D_3BFD_40F8_9FB9_6AF477298A68 */
