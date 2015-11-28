//
// Created by ezhang on 2015-11-26.
//

#ifndef WIFFWUFF_TILE_ESCAPE_WIN_H
#define WIFFWUFF_TILE_ESCAPE_WIN_H


#include "basetile.h"

namespace wumpus_game {
    class Tile_escape_win : public BaseTile{
    public:

        using BaseTile::BaseTile;

        Tile_escape_win(const std::size_t &tile_id);

        virtual bool EnterCharacter(std::shared_ptr<BaseUnit> ptr) override;

        virtual bool MoveCharacter(const std::string &name, const std::string &direction) override;
        virtual void PrintTileDependentInformation() override;

        void finish_game();



    };
}


#endif //WIFFWUFF_TILE_ESCAPE_WIN_H
