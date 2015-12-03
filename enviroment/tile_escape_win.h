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

        virtual double attack_damage_mod_tile(const std::string &unit_name);

        virtual void PrintPlayerOptionAndInformation() override;

        virtual std::pair<bool, std::string> unit_can_attack_here(std::string unit_name);
    };
}


#endif //WIFFWUFF_TILE_ESCAPE_WIN_H
