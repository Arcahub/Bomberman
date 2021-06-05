# Install script for directory: /home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-src/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/bullet" TYPE FILE FILES
    "/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-src/src/btBulletCollisionCommon.h"
    "/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-src/src/btBulletDynamicsCommon.h"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-build/src/Bullet3OpenCL/cmake_install.cmake")
  include("/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-build/src/Bullet3Serialize/Bullet2FileLoader/cmake_install.cmake")
  include("/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-build/src/Bullet3Dynamics/cmake_install.cmake")
  include("/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-build/src/Bullet3Collision/cmake_install.cmake")
  include("/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-build/src/Bullet3Geometry/cmake_install.cmake")
  include("/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-build/src/BulletInverseDynamics/cmake_install.cmake")
  include("/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-build/src/BulletSoftBody/cmake_install.cmake")
  include("/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-build/src/BulletCollision/cmake_install.cmake")
  include("/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-build/src/BulletDynamics/cmake_install.cmake")
  include("/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-build/src/LinearMath/cmake_install.cmake")
  include("/home/mathias/Epitech/Teck2/B-YEP-400-TLS-4-1-indiestudio-guillaume.mailhol/cmake-build-default/_deps/bullet3-build/src/Bullet3Common/cmake_install.cmake")

endif()

