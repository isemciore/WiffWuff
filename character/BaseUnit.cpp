//
// Created by erik on 2015-11-10.
//

#include <iostream>
#include "BaseUnit.h"
#include "../enviroment/BaseTile.h"



wumpus_game::BaseUnit::~BaseUnit() {

}

void wumpus_game::BaseUnit::SetTilePointer(std::weak_ptr<BaseTile> baseTp) {
    location_tile_pointer_ = baseTp;
}

wumpus_game::BaseUnit::BaseUnit(std::string name, std::weak_ptr<BaseTile> initPosition)
    : location_tile_pointer_(initPosition)
    , unit_name_(name){
}

void wumpus_game::BaseUnit::PerformAction() {
    std::cout << "I am character "<< unit_name_ << "\n";

}

bool wumpus_game::BaseUnit::travel(std::string direction) {
    return location_tile_pointer_.lock()->move_char(unit_name_,direction);

}
