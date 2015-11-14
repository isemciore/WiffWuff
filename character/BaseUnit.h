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
        std::weak_ptr<BaseTile> location_tile_pointer_;
        std::string unit_name_;
    public:
        BaseUnit();
        BaseUnit(std::string name, std::weak_ptr<BaseTile> initPosition);
        BaseUnit(const BaseUnit &);
        ~BaseUnit();

        void SetTilePointer(std::weak_ptr<BaseTile> baseTp);
        void PerformAction();
        std::weak_ptr<BaseTile> GetUnitLocation() {
            return location_tile_pointer_;
        }
        std::string get_unit_name(){return unit_name_;};

        void outputStuff();
        void callOther();

    };

}

#endif //WIFFWUFF_BASE_UNIT_H
