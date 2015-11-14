//
// Created by erik on 2015-11-10.
//

#include <iostream>
#include "BaseUnit.h"
#include "../enviroment/BaseTile.h"

wumpus_game::BaseUnit::BaseUnit() {

}

wumpus_game::BaseUnit::BaseUnit(const wumpus_game::BaseUnit &unit) {

}

wumpus_game::BaseUnit::~BaseUnit() {

}


void wumpus_game::BaseUnit::outputStuff() {
    std::cout << "BASE UNIT WRITING STUFF \n";
}

void wumpus_game::BaseUnit::callOther() {
    _baseTp.lock()->OutputStuff();
}

void wumpus_game::BaseUnit::SetTilePointer(std::weak_ptr<BaseTile> baseTp) {
    _baseTp = baseTp;
}
