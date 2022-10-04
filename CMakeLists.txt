cmake_minimum_required(VERSION 3.0.0)
# project(ProjetBTD VERSION 0.1.0)
SET(PROJ_NAME "ProjetBTD")
project(${PROJ_NAME} VERSION 0.1.0)


# Configuration types
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
IF(DEFINED CMAKE_BUILD_TYPE AND CMAKE_VERSION VERSION_GREATER "2.8")
 SET_PROPERTY(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS ${CMAKE_CONFIGURATION_TYPES})
# SET_PROPERTY(CACHE DCMAKE_BUILD_TYPE PROPERTY STRINGS "Release")
ENDIF()
SET(${PROJ_NAME}_PATH_INSTALL "/opt/project" CACHE PATH "This
directory contains installation Path")
SET(CMAKE_DEBUG_POSTFIX "d")

INCLUDE_DIRECTORIES(
    C:/vcpkg/installed/x64-windows/include/
)
  
LINK_DIRECTORIES(
    C:/vcpkg/installed/x64-windows/lib/
)
add_executable(${PROJ_NAME} src/main.cpp)
TARGET_LINK_LIBRARIES(${PROJ_NAME} 
    raylib
)