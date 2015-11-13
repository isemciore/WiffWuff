//
// Created by erik on 2015-11-13.
//

#ifndef WIFFWUFF_TILE_OCEAN_H
#define WIFFWUFF_TILE_OCEAN_H

#include "base_tile.h"

namespace wumpus_game {

    class tile_ocean : public base_tile{
        using base_tile::base_tile;
    public:
        virtual void outputStuff() override ;
        void outputNonVirtStuff();
    };

}

#endif //WIFFWUFF_TILE_OCEAN_H
