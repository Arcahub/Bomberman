set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SHARED_MODULE_PREFIX "")

include(FetchContent)

set(bomberman_MAIN "src/main.cpp")

set(bomberman_lib_SOURCES
    "src/RootState.cpp"
    "src/AStar.cpp"
    "src/Player.cpp"
    "src/scripts/TrackballCamera.cpp"
    "src/scripts/PlayerController.cpp"
    "src/scripts/CharacterController.cpp"
    "src/scripts/Bomb.cpp"
    "src/scripts/MapGenerator.cpp"
    "src/scripts/AIController.cpp"
    "src/scripts/SoloController.cpp"
    "src/plugin/NetworkPlugin.cpp"
    "src/plugin/network/NetworkManager.cpp"
    "src/plugin/network/NetworkId.cpp"
    "src/plugin/network/Client.cpp"
    "src/plugin/network/Server.cpp"
    "src/plugin/network/Packet.cpp"
    "src/plugin/RoomPlugin.cpp"
    "src/plugin/room/Room.cpp"
    "src/plugin/room/RoomClient.cpp"
    "src/plugin/room/RoomServer.cpp"
    "src/plugin/room/RoomPlayer.cpp"
    "src/plugin/room/RoomPacket.cpp"
    "src/plugin/BombermanLobbyPlugin.cpp"
    )

    set(bomberman_lib_HEADERS
    "include/RootState.hpp"
    "include/AStar.hpp"
    "include/Tag.hpp"
    "include/Player.hpp"
    "include/plugin/NetworkPlugin.hpp"
    "include/plugin/network/NetworkManager.hpp"
    "include/plugin/network/NetworkId.hpp"
    "include/plugin/network/Packet.hpp"
    "include/plugin/RoomPlugin.hpp"
    "include/plugin/room/Room.hpp"
    "include/plugin/room/RoomClient.hpp"
    "include/plugin/room/RoomServer.hpp"
    "include/plugin/room/RoomPlayer.hpp"
    "include/plugin/room/RoomPlayer.hpp"
    "include/plugin/room/RoomPacket.hpp"
    "include/plugin/BombermanLobbyPlugin.hpp"
    "include/scripts/TrackballCamera.hpp"
    "include/scripts/PlayerController.hpp"
    "include/scripts/CharacterController.hpp"
    "include/scripts/Bomb.hpp"
    "include/scripts/MapGenerator.hpp"
    "include/scripts/AIController.hpp"
    "include/scripts/SoloController.hpp"
)

add_library(bomberman_lib ${bomberman_lib_SOURCES} ${bomberman_lib_HEADERS})
target_include_directories(bomberman_lib PUBLIC "include")
target_link_libraries(bomberman_lib ige)

if (UNIX)
    add_executable(bomberman ${bomberman_MAIN})
else()
    add_executable(bomberman WIN32 ${bomberman_MAIN})
endif()
    target_link_libraries(bomberman bomberman_lib)
