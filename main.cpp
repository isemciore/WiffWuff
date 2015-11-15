#include <iostream>
#include <memory>
#include "character/baseunit.h"
#include "enviroment/basetile.h"
#include "enviroment/tile_ocean.h"
#include "gamemaster.h"

using namespace wumpus_game;


int main() {
    std::cout << "Hello, World!" << std::endl;

    GameMaster gameEvent;
    gameEvent.GameStart();




    return 0;
}