//
// Created by erik on 2015-11-10.
//

#include <iostream>
#include "base_tile.h"
#include "../character/base_unit.h"

wumpus_game::base_tile::base_tile() {

}

wumpus_game::base_tile::base_tile(const wumpus_game::base_tile &tile) {

}

wumpus_game::base_tile::~base_tile() {

}

void wumpus_game::base_tile::setUnitPointer(std::weak_ptr<base_unit> baseUp) {
    _baseUp = baseUp;
}

void wumpus_game::base_tile::outputStuff() {
    std::cout << "BASE TILE WRITING STUFF \n";
}

void wumpus_game::base_tile::callOther() {
    _baseUp.lock()->outputStuff();
}

void wumpus_game::base_tile::outputNonVirtStuff() {
    std::cout << "base_tile writing \n";
}
