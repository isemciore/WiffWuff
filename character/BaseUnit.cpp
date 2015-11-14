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
    location_tile_pointer_.lock()->OutputStuff();
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
