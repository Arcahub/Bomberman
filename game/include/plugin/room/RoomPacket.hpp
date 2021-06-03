#ifndef D118AB35_5791_4510_A462_51CBD82A1200
#define D118AB35_5791_4510_A462_51CBD82A1200

#include "plugin/network/NetworkId.hpp"
#include "plugin/network/Packet.hpp"

enum class RoomPacketType {
    ROOM_JOIN,
    ROOM_UPDATE,
    ROOM_LEAVE,
    PLAYER_JOIN,
    PLAYER_UPDATE,
};

class RoomPacket : public Packet {
public:
    RoomPacketType type;
    NetworkId netword_id;
};

#endif /* D118AB35_5791_4510_A462_51CBD82A1200 */
