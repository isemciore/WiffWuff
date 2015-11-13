#include <iostream>
#include <memory>
#include "character/base_unit.h"
#include "enviroment/base_tile.h"
#include "enviroment/tile_ocean.h"

using namespace wumpus_game;


int main() {
    std::cout << "Hello, World!" << std::endl;

    std::shared_ptr<base_tile> tilePointer;
    tilePointer.reset(new tile_ocean());

    std::shared_ptr<base_unit> unitPointer;
    unitPointer.reset(new base_unit());

    tilePointer->setUnitPointer(unitPointer);
    unitPointer->setTilePointer(tilePointer);

    tilePointer->callOther();
    unitPointer->callOther();

    std::shared_ptr<tile_ocean> oceanTileSP;
    oceanTileSP = std::dynamic_pointer_cast<tile_ocean>(tilePointer);
    oceanTileSP->outputStuff();
    oceanTileSP->outputNonVirtStuff();



    return 0;
}