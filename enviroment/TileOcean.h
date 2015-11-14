//
// Created by erik on 2015-11-13.
//

#ifndef WIFFWUFF_TILE_OCEAN_H
#define WIFFWUFF_TILE_OCEAN_H

#include "BaseTile.h"

namespace wumpus_game {

    class TileOcean : public BaseTile {

    public:
        using BaseTile::BaseTile;
        TileOcean(std::size_t tile_id);
        virtual void OutputStuff() override ;
        void outputNonVirtStuff();
    };

}

#endif //WIFFWUFF_TILE_OCEAN_H
