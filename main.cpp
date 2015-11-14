#include <iostream>
#include <memory>
#include "character/BaseUnit.h"
#include "enviroment/BaseTile.h"
#include "enviroment/TileOcean.h"
#include "GameMaster.h"

using namespace wumpus_game;


int main() {
    std::cout << "Hello, World!" << std::endl;

    GameMaster gameEvent;
    gameEvent.GameStart();




    return 0;
}