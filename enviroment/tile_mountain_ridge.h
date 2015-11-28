//
// Created by ezhang on 2015-11-15.
//

#ifndef WIFFWUFF_TILE_MOUNTAIN_RIDGE_H
#define WIFFWUFF_TILE_MOUNTAIN_RIDGE_H


#include "basetile.h"

namespace wumpus_game {
    class TileMountainRidge :public BaseTile {
    public:
        using BaseTile::BaseTile;

        TileMountainRidge(const std::size_t &tile_id);

        virtual void PrintTileDependentInformation();
    };

}


#endif //WIFFWUFF_TILE_MOUNTAIN_RIDGE_H
