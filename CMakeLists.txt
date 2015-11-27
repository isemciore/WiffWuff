cmake_minimum_required(VERSION 3.3)
project(WiffWuff)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp gamemaster.cpp gamemaster.h character/baseunit.cpp character/baseunit.h
        enviroment/basetile.cpp enviroment/basetile.h enviroment/tile_ocean.cpp enviroment/tile_ocean.h
        stuff/Item.cpp stuff/Item.h character/npc.cpp character/npc.h character/PlayerCtrl.cpp
        character/PlayerCtrl.h stuff/Consumable.cpp stuff/Consumable.h stuff/container.cpp
        stuff/container.h gamesave.cpp gamesave.h character/paladin.cpp character/paladin.h
        character/turtle.cpp character/turtle.h character/wumpus.cpp character/wumpus.h enviroment/tile_mountain_ridge.cpp enviroment/tile_mountain_ridge.h enviroment/tile_dark_room.cpp enviroment/tile_dark_room.h enviroment/tile_escape_win.cpp enviroment/tile_escape_win.h character/sorcerer.cpp character/sorcerer.h)
add_executable(WiffWuff ${SOURCE_FILES})