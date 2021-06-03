# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.19.2)

# We name the project and the target for the ExternalProject_Add() call
# to something that will highlight to the user what we are working on if
# something goes wrong and an error message is produced.

project(bullet3-populate NONE)

include(ExternalProject)
ExternalProject_Add(bullet3-populate
                     "UPDATE_DISCONNECTED" "False" "GIT_REPOSITORY" "https://github.com/bulletphysics/bullet3.git" "GIT_TAG" "3.17"
                    SOURCE_DIR          "/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-src"
                    BINARY_DIR          "/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-build"
                    CONFIGURE_COMMAND   ""
                    BUILD_COMMAND       ""
                    INSTALL_COMMAND     ""
                    TEST_COMMAND        ""
                    USES_TERMINAL_DOWNLOAD  YES
                    USES_TERMINAL_UPDATE    YES
)


