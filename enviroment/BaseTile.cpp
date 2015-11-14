//
// Created by erik on 2015-11-10.
//

#include <iostream>
#include "BaseTile.h"
#include "../character/BaseUnit.h"

wumpus_game::BaseTile::BaseTile() {

}

wumpus_game::BaseTile::BaseTile(const wumpus_game::BaseTile &tile) {

}

wumpus_game::BaseTile::~BaseTile() {

}

void wumpus_game::BaseTile::SetUnitPointer(std::weak_ptr<BaseUnit> baseUp) {
    _baseUp = baseUp;
}

void wumpus_game::BaseTile::OutputStuff() {
    std::cout << "BASE TILE WRITING STUFF \n";
}

void wumpus_game::BaseTile::callOther() {
    _baseUp.lock()->outputStuff();
}

void wumpus_game::BaseTile::outputNonVirtStuff() {
    std::cout << "BaseTile writing \n";
}
