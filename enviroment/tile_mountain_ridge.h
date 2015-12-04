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

        TileMountainRidge(const int &tile_id);

        virtual std::pair<bool, std::string> unit_can_attack_here(std::string unit_name);

        virtual double attack_damage_mod_tile(const std::string &unit_name);

        virtual void PrintTileDependentInformation();
    };

}


#endif //WIFFWUFF_TILE_MOUNTAIN_RIDGE_H
