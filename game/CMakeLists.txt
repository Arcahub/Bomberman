set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SHARED_MODULE_PREFIX "")

include(FetchContent)

set(bomberman_MAIN "src/main.cpp")

set(bomberman_lib_SOURCES
    "src/RootState.cpp"
    "src/AStar.cpp"
    "src/scripts/TrackballCamera.cpp"
    "src/scripts/PlayerController.cpp"
    "src/scripts/CharacterController.cpp"
    "src/scripts/NetworkController.cpp"
    "src/scripts/Bomb.cpp"
    "src/scripts/MapGenerator.cpp"
    "src/scripts/AIController.cpp"
    "src/scripts/SoloController.cpp"
    "src/concurrent/SynchroRinger.cpp"
    "src/plugin/NetworkPlugin.cpp"
    "src/plugin/network/NetworkManager.cpp"
    "src/plugin/network/NetworkId.cpp"
    "src/plugin/network/NetClient.cpp"
    "src/plugin/network/Server.cpp"
    "src/plugin/network/Client.cpp"
    "src/plugin/network/Packet.cpp"
    "src/plugin/RoomPlugin.cpp"
    "src/plugin/room/Room.cpp"
    "src/plugin/room/RoomClient.cpp"
    "src/plugin/room/RoomServer.cpp"
    "src/plugin/room/RoomPacket.cpp"
    "src/plugin/BombermanLobbyPlugin.cpp"
    "src/bomberman_lobby/BombermanLobby.cpp"
    "src/bomberman_lobby/packets/PlayerInputsPacket.cpp"
    "src/bomberman_lobby/packets/LobbySettingsPacket.cpp"
    "src/bomberman_lobby/packets/PlayerLeavePacket.cpp"
    "src/bomberman_lobby/packets/PlayerJoinPacket.cpp"
    "src/bomberman_lobby/packets/RoomJoinPacket.cpp"
    "src/bomberman_lobby/packets/RoomClosePacket.cpp"
    )

    set(bomberman_lib_HEADERS
    "include/RootState.hpp"
    "include/AStar.hpp"
    "include/Tag.hpp"
    "include/concurrent/ConcurrentVector.hpp"
    "include/concurrent/ConcurrentQueue.hpp"
    "include/concurrent/SynchroRinger.hpp"
    "include/plugin/NetworkPlugin.hpp"
    "include/plugin/network/Utils.hpp"
    "include/plugin/network/Server.hpp"
    "include/plugin/network/Client.hpp"
    "include/plugin/network/NetClient.hpp"
    "include/plugin/network/NetworkManager.hpp"
    "include/plugin/network/NetworkId.hpp"
    "include/plugin/network/Packet.hpp"
    "include/plugin/network/SynchroThreadBuffer.hpp"
    "include/plugin/RoomPlugin.hpp"
    "include/plugin/room/Room.hpp"
    "include/plugin/room/RoomClient.hpp"
    "include/plugin/room/RoomServer.hpp"
    "include/plugin/room/RoomPlayer.hpp"
    "include/plugin/room/RoomPlayer.hpp"
    "include/plugin/room/RoomPlayerId.hpp"
    "include/plugin/room/RoomPacket.hpp"
    "include/plugin/BombermanLobbyPlugin.hpp"
    "include/bomberman_lobby/BombermanLobby.hpp"
    "include/bomberman_lobby/BombermanPacket.hpp"
    "include/bomberman_lobby/packets/GameStartPacket.hpp"
    "include/bomberman_lobby/packets/LobbySettingsPacket.hpp"
    "include/bomberman_lobby/packets/PlayerInputsPacket.hpp"
    "include/bomberman_lobby/packets/RoomJoinPacket.hpp"
    "include/bomberman_lobby/packets/RoomSettingsUpdate.hpp"
)

add_library(bomberman_lib ${bomberman_lib_SOURCES} ${bomberman_lib_HEADERS})
target_include_directories(bomberman_lib PUBLIC "include")
target_link_libraries(bomberman_lib ige inl)

add_executable(bomberman ${bomberman_MAIN})

if(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DOPEN_CONSOLE")
    set_target_properties(bomberman PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
    set_target_properties(bomberman PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
    set_target_properties(bomberman PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:windows")
    set_target_properties(bomberman PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:windows")
endif()

target_link_libraries(bomberman bomberman_lib)
