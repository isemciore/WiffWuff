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

bool wumpus_game::BaseUnit::Travel(std::vector<std::string> direction) {
    return location_tile_pointer_.lock()->move_char(unit_name_,direction[1]);

}

bool wumpus_game::BaseUnit::Attack(std::vector<std::string> vec_command_argument) {
    //attack turtle1, ie target in elt 1
    location_tile_pointer_.lock()->attack_action(unit_name_,vec_command_argument[1]);
    return false;
}

bool wumpus_game::BaseUnit::attack_in_water() {
    return can_attack_in_water_;
}

bool wumpus_game::BaseUnit::RecieveDamage(int damage_taken_b4_reduction) {
    current_health-=damage_taken_b4_reduction;
    std::cout << unit_name_ << " recieves "<< damage_taken_b4_reduction << " after armor red\n";
    if(current_health<1){
        return false;
    }
    return true;
}
