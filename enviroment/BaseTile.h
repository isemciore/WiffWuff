//
// Created by erik on 2015-11-10.
//

#ifndef WIFFWUFF_BASE_TILE_H
#define WIFFWUFF_BASE_TILE_H
#include <memory>

namespace wumpus_game {
    class BaseUnit;
    
    class BaseTile {
    protected:
        std::weak_ptr<BaseUnit> _baseUp;

    public:
        BaseTile();
        BaseTile(const BaseTile &);
        ~BaseTile();

        void SetUnitPointer(std::weak_ptr<BaseUnit> baseUp);
        virtual void OutputStuff();
        void outputNonVirtStuff();
        void callOther();

    };

}

#endif //WIFFWUFF_BASE_TILE_H
