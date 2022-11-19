cmake_minimum_required(VERSION 3.0.0)
# project(ProjetBTD VERSION 0.1.0)
SET(PROJ_NAME "ProjetBTD")
project(${PROJ_NAME} VERSION 0.1.0)

INCLUDE_DIRECTORIES(
    C:/vcpkg/installed/x64-windows/include/
)
  
LINK_DIRECTORIES(
    C:/vcpkg/installed/x64-windows/lib/
)
add_executable(${PROJ_NAME} src/test.cpp)
TARGET_LINK_LIBRARIES(${PROJ_NAME} 
    raylib
)