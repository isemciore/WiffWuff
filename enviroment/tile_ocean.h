//
// Created by erik on 2015-11-13.
//

#ifndef WIFFWUFF_TILE_OCEAN_H
#define WIFFWUFF_TILE_OCEAN_H

#include "basetile.h"

namespace wumpus_game {

    class TileOcean : public BaseTile {

    public:
        using BaseTile::BaseTile;

        TileOcean(const std::size_t &tile_id);

        virtual void PrintTileDependentInformation();

        virtual bool AddItem(Item *item1) override;

        virtual bool AttackAction(const std::string &attacker, const std::string &attacked) override;

        virtual bool shoot_able_from_room();
    };

}

#endif //WIFFWUFF_TILE_OCEAN_H
