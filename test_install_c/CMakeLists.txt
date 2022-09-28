cmake_minimum_required(VERSION 3.0.0)
project(TestRaylib VERSION 0.1.0)
INCLUDE_DIRECTORIES(
    C:/vcpkg/installed/x64-windows/include/
)
  
LINK_DIRECTORIES(
    C:/vcpkg/installed/x64-windows/lib/
)
add_executable(TestRaylib main.cpp)
# add_executable(TestRaylib some.cpp)
TARGET_LINK_LIBRARIES(TestRaylib
    raylib
)