set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SHARED_MODULE_PREFIX "")

include(FetchContent)

set(bomberman_MAIN "src/main.cpp")

set(bomberman_lib_SOURCES
    "src/lib.cpp"
)

set(bomberman_lib_HEADERS
    "include/lib.hpp"
)

add_library(bomberman_lib ${bomberman_lib_SOURCES} ${bomberman_lib_HEADERS})
target_include_directories(bomberman_lib PUBLIC "include")
target_link_libraries(bomberman_lib ige)
add_executable(bomberman ${bomberman_MAIN})
target_link_libraries(bomberman bomberman_lib)
