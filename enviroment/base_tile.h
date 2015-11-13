//
// Created by erik on 2015-11-10.
//

#ifndef WIFFWUFF_BASE_TILE_H
#define WIFFWUFF_BASE_TILE_H
#include <memory>

namespace wumpus_game {
    class base_unit;
    
    class base_tile {
    protected:
        std::weak_ptr<base_unit> _baseUp;

    public:
        base_tile();
        base_tile(const base_tile&);
        ~base_tile();

        void setUnitPointer(std::weak_ptr<base_unit> baseUp);
        virtual void outputStuff();
        void outputNonVirtStuff();
        void callOther();

    };

}

#endif //WIFFWUFF_BASE_TILE_H
