cmake_minimum_required(VERSION 3.3)
project(WiffWuff)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp GameMaster.cpp GameMaster.h character/base_unit.cpp character/base_unit.h enviroment/base_tile.cpp enviroment/base_tile.h enviroment/tile_ocean.cpp enviroment/tile_ocean.h stuff/item.cpp stuff/item.h character/npc.cpp character/npc.h character/player_ctrl.cpp character/player_ctrl.h stuff/consumable.cpp stuff/consumable.h stuff/container.cpp stuff/container.h gameSave.cpp gameSave.h)
add_executable(WiffWuff ${SOURCE_FILES})