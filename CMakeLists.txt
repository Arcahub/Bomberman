cmake_minimum_required(VERSION 3.17)

project(bomberman)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SHARED_MODULE_PREFIX "")

include(FetchContent)

# Fetch ige
FetchContent_Declare(
    ige
    GIT_REPOSITORY https://github.com/nasso/ige.git
    GIT_TAG origin/stable
)
FetchContent_GetProperties(ige)
if(NOT ige_POPULATED)
    FetchContent_Populate(ige)
    set(IGE_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(IGE_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory(${ige_SOURCE_DIR})
endif()

add_subdirectory(game)

set_target_properties(bomberman
    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}"
)

if (BUILD_INSTALLER)
    install(TARGETS bomberman
        DESTINATION "." COMPONENT bomberman_app)
    install(DIRECTORY "assets"
        DESTINATION "." COMPONENT bomberman_app)
    include(CpackConfig)
endif()
