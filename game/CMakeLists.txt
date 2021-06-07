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
)

set(bomberman_lib_HEADERS
    "include/RootState.hpp"
    "include/scripts.hpp"
    "include/scripts/TrackballCamera.hpp"
    "include/scripts/PlayerController.hpp"
    "include/scripts/CharacterController.hpp"
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
