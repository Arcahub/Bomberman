# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.19.2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(glfw-populate NONE)

include(ExternalProject)
ExternalProject_Add(glfw-populate
                     "UPDATE_DISCONNECTED" "False" "URL" "https://github.com/glfw/glfw/releases/download/3.3.4/glfw-3.3.4.zip" "URL_HASH" "SHA1=29ce5f24fede4935b4872606df1e987400c9d060"
                    SOURCE_DIR          "/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/glfw-src"
                    BINARY_DIR          "/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/glfw-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


