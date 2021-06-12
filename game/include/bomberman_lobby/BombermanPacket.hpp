#ifndef DB85CE1D_3BFD_40F8_9FB9_6AF477298A68
#define DB85CE1D_3BFD_40F8_9FB9_6AF477298A68

#include "plugin/room/RoomPacket.hpp"
#include <vector>

#include "packets/GameStartPacket.hpp"
#include "packets/LobbySettingsPacket.hpp"
#include "packets/PlayerInputsPacket.hpp"
#include "packets/PlayerJoinPacket.hpp"
#include "packets/PlayerLeavePacket.hpp"
#include "packets/RoomClosePacket.hpp"
#include "packets/RoomJoinPacket.hpp"
#include "packets/RoomSettingsUpdate.hpp"

/*
Player - Server
-> Connect to server
<- Accept connection
<- Send room infos
<-> Room Settings Update
-> Request game launch
<- Send game info (spawn, map, etc)
<-> Send players infos / room update
<- Game end
<- Room closed
*/

enum class BombermanPacketType {
    ROOM_JOIN,
    ROOM_SETTINGS_UPDATE,
    ROOM_UPDATE,
    ROOM_CLOSE,
    PLAYER_STARTED_GAME,
    GAME_START,
    PLAYER_JOIN,
    PLAYER_INPUTS,
    PLAYER_LEAVE,
};

#endif /* DB85CE1D_3BFD_40F8_9FB9_6AF477298A68 */
