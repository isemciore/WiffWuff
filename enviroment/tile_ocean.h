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

        TileOcean(const int &tile_id);

        virtual void PrintTileDependentInformation();

        virtual bool AddItem(Item *item1) override;

        //virtual bool attack_action(std::string attacker, std::string attacked) override;

        virtual std::pair<bool, std::string> unit_can_attack_here(std::string unit_name);

        virtual bool shoot_able_from_room();

        virtual double attack_damage_mod_tile(const std::string &unit_name);
    };

}

#endif //WIFFWUFF_TILE_OCEAN_H
