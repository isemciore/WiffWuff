//
// Created by erik on 2015-11-10.
//

#include <iostream>
#include "base_unit.h"
#include "../enviroment/base_tile.h"

wumpus_game::base_unit::base_unit() {

}

wumpus_game::base_unit::base_unit(const wumpus_game::base_unit &unit) {

}

wumpus_game::base_unit::~base_unit() {

}

void wumpus_game::base_unit::setTilePointer(std::weak_ptr<base_tile> baseTp) {
    _baseTp = baseTp;
}

void wumpus_game::base_unit::outputStuff() {
    std::cout << "BASE UNIT WRITING STUFF \n";
}

void wumpus_game::base_unit::callOther() {
    _baseTp.lock()->outputStuff();
}
