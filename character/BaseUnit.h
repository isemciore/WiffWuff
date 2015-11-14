//
// Created by erik on 2015-11-10.
//

#ifndef WIFFWUFF_BASE_UNIT_H
#define WIFFWUFF_BASE_UNIT_H

#include <memory>
#include "../enviroment/BaseTile.h"


namespace wumpus_game {
    class BaseTile;

    class BaseUnit {
    protected:
        std::weak_ptr<BaseTile> _baseTp;

    public:
        BaseUnit();
        BaseUnit(const BaseUnit &);
        ~BaseUnit();

        void SetTilePointer(std::weak_ptr<BaseTile> baseTp);
        void PerformAction(){};


        void outputStuff();
        void callOther();

    };

}

#endif //WIFFWUFF_BASE_UNIT_H
