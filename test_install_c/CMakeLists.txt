cmake_minimum_required(VERSION 3.0.0)
project(TestSQL VERSION 0.1.0)
INCLUDE_DIRECTORIES(
  c:/vcpkg/installed/x64-windows/include/
)
  
LINK_DIRECTORIES(
  c:/vcpkg/installed/x64-windows/lib/
)
add_executable(TestSQL main.cpp)
TARGET_LINK_LIBRARIES(TestSQL
  sqlite3 raylib
)