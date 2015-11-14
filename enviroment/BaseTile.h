//
// Created by erik on 2015-11-10.
//

#ifndef WIFFWUFF_BASE_TILE_H
#define WIFFWUFF_BASE_TILE_H
#include <memory>
#include <map>
#include "../character/BaseUnit.h"

namespace wumpus_game {
    class BaseUnit;
    
    class BaseTile {
    protected:
        std::size_t tile_id_;
        std::map<std::string,std::shared_ptr<BaseUnit>> map_of_char_in_tile_;

        //debugging purp
        std::weak_ptr<BaseUnit> _baseUp_;

    public:
        BaseTile(std::size_t);
        BaseTile(const BaseTile &);
        ~BaseTile();

        void SetUnitPointer(std::weak_ptr<BaseUnit> baseUp);
        bool AddCharToTile(std::shared_ptr<BaseUnit>);



        virtual void OutputStuff();
        void outputNonVirtStuff();
        void callOther();

    };

}

#endif //WIFFWUFF_BASE_TILE_H
