set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SHARED_MODULE_PREFIX "")

include(FetchContent)

set(bomberman_MAIN "src/main.cpp")

set(bomberman_lib_SOURCES
    "src/RootState.cpp"
    "src/RoomState.cpp"
    "src/AStar.cpp"
    "src/matchmaking/Matchmaking.cpp"
    "src/utils/map/MapGeneration.cpp"
    "src/utils/map/MapLoading.cpp"
    "src/utils/CsvUtils.cpp"
    "src/scripts/TrackballCamera.cpp"
    "src/scripts/PlayerController.cpp"
    "src/scripts/CharacterController.cpp"
    "src/scripts/NetworkController.cpp"
    "src/scripts/Bomb.cpp"
    "src/scripts/MapGenerator.cpp"
    "src/scripts/AIController.cpp"
    "src/scripts/SoloController.cpp"
    "src/scripts/MysteryBox.cpp"
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
    "src/MenuState.cpp"
)

set(bomberman_lib_HEADERS
    "include/RootState.hpp"
    "include/RoomState.hpp"
    "include/AStar.hpp"
    "include/Tag.hpp"
    "include/matchmaking/Matchmaking.hpp"
    "include/network/Http.hpp"
    "include/utils/map/MapGeneration.hpp"
    "include/utils/map/MapLoading.hpp"
    "include/utils/CsvUtils.hpp"
    "include/concurrent/ConcurrentVector.hpp"
    "include/concurrent/ConcurrentQueue.hpp"
    "include/concurrent/SynchroRinger.hpp"
    "include/plugin/NetworkPlugin.hpp"
    "include/plugin/network/NetworkUtils.hpp"
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
    "include/scripts/TrackballCamera.hpp"
    "include/scripts/PlayerController.hpp"
    "include/scripts/CharacterController.hpp"
    "include/scripts/NetworkController.hpp"
    "include/scripts/Bomb.hpp"
    "include/scripts/MapGenerator.hpp"
    "include/scripts/AIController.hpp"
    "include/scripts/SoloController.hpp"
    "include/scripts/MysteryBox.hpp"
    "include/MenuState.hpp"
)

if(WIN32)
  set(bomberman_lib_HEADERS ${bomberman_lib_HEADERS}
    "include/plugin/DiscordPlugin.hpp"
    "include/discord/achievement_manager.h"
    "include/discord/activity_manager.h"
    "include/discord/application_manager.h"
    "include/discord/core.h"
    "include/discord/discord.h"
    "include/discord/discord_game_sdk.h"
    "include/discord/event.h"
    "include/discord/ffi.h"
    "include/discord/image_manager.h"
    "include/discord/lobby_manager.h"
    "include/discord/network_manager.h"
    "include/discord/overlay_manager.h"
    "include/discord/relationship_manager.h"
    "include/discord/storage_manager.h"
    "include/discord/store_manager.h"
    "include/discord/types.h"
    "include/discord/user_manager.h"
    "include/discord/voice_manager.h"
  )

  set(bomberman_lib_SOURCES ${bomberman_lib_SOURCES}
    "src/discord/achievement_manager.cpp"
    "src/discord/activity_manager.cpp"
    "src/discord/application_manager.cpp"
    "src/discord/core.cpp"
    "src/discord/image_manager.cpp"
    "src/discord/lobby_manager.cpp"
    "src/discord/network_manager.cpp"
    "src/discord/overlay_manager.cpp"
    "src/discord/relationship_manager.cpp"
    "src/discord/storage_manager.cpp"
    "src/discord/store_manager.cpp"
    "src/discord/types.cpp"
    "src/discord/user_manager.cpp"
    "src/discord/voice_manager.cpp"
    "src/plugin/DiscordPlugin.cpp"
  )
endif()

## Get nlhomann json parser
FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.7.3)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(CMAKE_DEBUG_POSTFIX "")

link_directories(${CMAKE_SOURCE_DIR}/dependencies)
add_library(bomberman_lib ${bomberman_lib_SOURCES} ${bomberman_lib_HEADERS})

target_include_directories(bomberman_lib PUBLIC "include")
target_link_libraries(bomberman_lib ige inl nlohmann_json::nlohmann_json)

if (WIN32)
  target_link_libraries(bomberman_lib discord_game_sdk)
endif()

add_executable(bomberman ${bomberman_MAIN})

if(WIN32)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DOPEN_CONSOLE")
    set_target_properties(bomberman PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
    set_target_properties(bomberman PROPERTIES COMPILE_DEFINITIONS_DEBUG "_CONSOLE")
    set_target_properties(bomberman PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:windows")
    set_target_properties(bomberman PROPERTIES LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:windows")

    add_custom_command(
    TARGET bomberman
    PRE_LINK COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_SOURCE_DIR}/dependencies/discord_game_sdk.dll
        $<TARGET_FILE:OpenAL>
        $<TARGET_FILE_DIR:bomberman>
)
endif()

target_link_libraries(bomberman bomberman_lib)
