cmake_minimum_required(VERSION 3.3)
project(WiffWuff)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp game_master.cpp game_master.h character/base_unit.cpp character/base_unit.h enviroment/base_tile.cpp enviroment/base_tile.h enviroment/tile_ocean.cpp enviroment/tile_ocean.h)
add_executable(WiffWuff ${SOURCE_FILES})