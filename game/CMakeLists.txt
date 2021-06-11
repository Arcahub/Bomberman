set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SHARED_MODULE_PREFIX "")

include(FetchContent)

set(bomberman_MAIN "src/main.cpp")

set(bomberman_lib_SOURCES
    "src/RootState.cpp"
    "src/scripts/TrackballCamera.cpp"
    "src/scripts/PlayerController.cpp"
    "src/scripts/CharacterController.cpp"
    "src/plugin/NetworkPlugin.cpp"
    "src/plugin/network/NetworkManager.cpp"
    "src/plugin/network/NetworkId.cpp"
    "src/plugin/network/NetClient.cpp"
    "src/plugin/network/Server.cpp"
    "src/plugin/network/Client.cpp"
    "src/plugin/network/Packet.cpp"
    "src/plugin/RoomPlugin.cpp"
    "src/concurrent/SynchroRinger.cpp"
)

set(bomberman_lib_HEADERS
    "include/concurrent/ConcurrentVector.hpp"
    "include/concurrent/ConcurrentQueue.hpp"
    "include/concurrent/SynchroRinger.hpp"
    "include/RootState.hpp"
    "include/scripts.hpp"
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
    "include/scripts/TrackballCamera.hpp"
    "include/scripts/PlayerController.hpp"
    "include/scripts/CharacterController.hpp"
)

add_library(bomberman_lib ${bomberman_lib_SOURCES} ${bomberman_lib_HEADERS})
target_include_directories(bomberman_lib PUBLIC "include")
target_link_libraries(bomberman_lib ige inl)

if (UNIX)
    add_executable(bomberman ${bomberman_MAIN})
else()
    add_executable(bomberman WIN32 ${bomberman_MAIN})
endif()
    target_link_libraries(bomberman bomberman_lib)
