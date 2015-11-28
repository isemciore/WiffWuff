#include <iostream>
#include <memory>
#include "character/baseunit.h"
#include "enviroment/basetile.h"
#include "enviroment/tile_ocean.h"
#include "gamemaster.h"

using namespace wumpus_game;


int main() {
    std::cout << "Start a new game or load game?" << std::endl;
    //load game, send data file to savefile type then gameEvent(savefile);

    GameMaster gameEvent;
    gameEvent.GameStart();




    return 0;
}