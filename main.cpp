#include <iostream>
#include <memory>
#include "character/BaseUnit.h"
#include "enviroment/BaseTile.h"
#include "enviroment/TileOcean.h"
#include "GameMaster.h"

using namespace wumpus_game;


int main() {
    std::cout << "Hello, World!" << std::endl;

    std::shared_ptr<BaseTile> tilePointer;
    tilePointer.reset(new TileOcean());

    std::shared_ptr<BaseUnit> unitPointer;
    unitPointer.reset(new BaseUnit());

    tilePointer->SetUnitPointer(unitPointer);
    unitPointer->SetTilePointer(tilePointer);

    tilePointer->callOther();
    unitPointer->callOther();

    std::shared_ptr<TileOcean> oceanTileSP;
    oceanTileSP = std::dynamic_pointer_cast<TileOcean>(tilePointer);
    oceanTileSP->OutputStuff();
    oceanTileSP->outputNonVirtStuff();



    GameMaster gameEvent;
    gameEvent.GameStart();




    return 0;
}