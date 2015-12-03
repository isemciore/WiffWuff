//
// Created by ezhang on 2015-11-15.
//

#include <iostream>
#include "tile_dark_room.h"

bool wumpus_game::TileDarkRoom::EnterCharacter(std::shared_ptr<wumpus_game::BaseUnit> ptr) {
    std::string srcName = ptr->get_unit_name();
    if(srcName == "Meep"){
        std::cout << "The room is too dark and you decide its best to turn around \n";
    }
    return false;
}

wumpus_game::TileDarkRoom::TileDarkRoom(const std::size_t &tile_id)
    : BaseTile(tile_id){
}

void wumpus_game::TileDarkRoom::PrintTileDependentInformation() {
}

std::pair<bool, std::string> wumpus_game::TileDarkRoom::unit_can_attack_here(std::string unit_name) {
    return std::make_pair(true, "-");
}
