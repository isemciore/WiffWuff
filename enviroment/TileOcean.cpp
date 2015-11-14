//
// Created by erik on 2015-11-13.
//

#include <iostream>
#include "TileOcean.h"



wumpus_game::TileOcean::TileOcean(std::size_t tile_id)
    : BaseTile(tile_id){
    DirectionFeasable[0] = true;
    DirectionFeasable[1] = true;
    DirectionFeasable[2] = true;
    DirectionFeasable[3] = true;

}
