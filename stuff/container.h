//
// Created by ezhang on 2015-11-13.
//

#ifndef WIFFWUFF_CONTAINER_H
#define WIFFWUFF_CONTAINER_H


#include "item.h"
#include <vector>
#include <memory>
#include <map>
#include "../enviroment/basetile.h"

namespace wumpus_game {
    class BaseTile;

    class container : public item{
        const double k_capacity_hold_weight_;
        const double k_capacity_hold_volume_;
        double currentWeight = 0;
        double currentVolume = 0;
        std::map<std::string,item*> item_container;


        typedef std::map<std::string,item*>::iterator item_container_iterator;
    public:
        container(std::string name, double holdWeight, double holdVolume);

        bool AddItem(item*);//If false, backpack broke


        void DropItemToTile(std::weak_ptr<BaseTile> tile_pointer);
        item* GetItem(std::string item_name);
    };
}


#endif //WIFFWUFF_CONTAINER_H
