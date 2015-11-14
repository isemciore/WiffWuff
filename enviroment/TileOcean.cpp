//
// Created by erik on 2015-11-13.
//

#include <iostream>
#include "TileOcean.h"

void wumpus_game::TileOcean::OutputStuff() {
    std::cout << "writing stuff from ocean \n";
}

void wumpus_game::TileOcean::outputNonVirtStuff() {
    std::cout <<"writing ocean non virtual \n";

}

wumpus_game::TileOcean::TileOcean(std::size_t tile_id)
    : BaseTile(tile_id){
}
