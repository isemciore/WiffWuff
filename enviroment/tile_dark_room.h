//
// Created by ezhang on 2015-11-15.
//

#ifndef WIFFWUFF_TILE_DARK_ROOM_H
#define WIFFWUFF_TILE_DARK_ROOM_H


#include "basetile.h"

namespace wumpus_game {
    class TileDarkRoom :public BaseTile {

    public:
        using BaseTile::BaseTile;
        TileDarkRoom(std::size_t tile_id);
        virtual bool enter(std::shared_ptr<BaseUnit> ptr) override;

        virtual bool unit_can_attack_here(std::string unit_name);

        virtual void PrintTileDependentInformation() override;
    };
}


#endif //WIFFWUFF_TILE_DARK_ROOM_H
