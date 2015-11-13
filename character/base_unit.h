//
// Created by erik on 2015-11-10.
//

#ifndef WIFFWUFF_BASE_UNIT_H
#define WIFFWUFF_BASE_UNIT_H

#include <memory>
#include "../enviroment/base_tile.h"


namespace wumpus_game {
    class base_tile;

    class base_unit {
    protected:
        std::weak_ptr<base_tile> _baseTp;

    public:
        base_unit();
        base_unit(const base_unit &);
        ~base_unit();

        void setTilePointer(std::weak_ptr<base_tile> baseTp);
        void outputStuff();

        void callOther();

    };

}

#endif //WIFFWUFF_BASE_UNIT_H
