//
// Created by erik on 2015-11-10.
//

#include <iostream>
#include "BaseTile.h"
#include "../character/BaseUnit.h"


wumpus_game::BaseTile::BaseTile(const wumpus_game::BaseTile &tile) {

}

wumpus_game::BaseTile::~BaseTile() {

}

void wumpus_game::BaseTile::SetUnitPointer(std::weak_ptr<BaseUnit> baseUp) {
    _baseUp_ = baseUp;
}

void wumpus_game::BaseTile::OutputStuff() {
    std::cout << "BASE TILE WRITING STUFF \n";
}

void wumpus_game::BaseTile::callOther() {
    _baseUp_.lock()->outputStuff();
}

void wumpus_game::BaseTile::outputNonVirtStuff() {
    std::cout << "BaseTile writing \n";
}

wumpus_game::BaseTile::BaseTile(size_t t)
    : tile_id_(t)
{
}

bool wumpus_game::BaseTile::AddCharToTile(std::shared_ptr<wumpus_game::BaseUnit> ptr) {
    std::string unit_name = ptr->get_unit_name();
    map_of_char_in_tile_.insert(std::make_pair(unit_name,ptr));
    return false;
}
