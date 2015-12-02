//
// Created by ezhang on 2015-11-15.
//

#include <iostream>
#include "tile_mountain_ridge.h"

wumpus_game::TileMountainRidge::TileMountainRidge(std::size_t tile_id)
    : BaseTile(tile_id){
    feaseable_direction[0] = true;
    feaseable_direction[1] = false;
    feaseable_direction[2] = true;
    feaseable_direction[3] = false;
}

void wumpus_game::TileMountainRidge::PrintTileDependentInformation() {
    std::cout << "You climb into a mountain ridge which restrict which direction you can travel\n";
}

bool wumpus_game::TileMountainRidge::unit_can_attack_here(std::string unit_name) {
    return true;
}
