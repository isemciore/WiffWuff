//
// Created by ezhang on 2015-11-13.
//

#ifndef WIFFWUFF_CONTAINER_H
#define WIFFWUFF_CONTAINER_H


#include "Item.h"
#include <vector>
#include <memory>
#include <map>
#include "../enviroment/basetile.h"

namespace wumpus_game {
    class BaseTile;

    class container : public Item {
        const double k_capacity_hold_weight_;
        const double k_capacity_hold_volume_;
        double internal_extra_weight = 0;
        double internal_extra_volume = 0;
        std::map<std::string, Item *> item_container;


        typedef std::map<std::string, Item *>::iterator item_container_iterator;
    public:
        virtual ~container();

        container(const std::string &name, const double &holdWeight, const double &holdVolume);

        bool AddItem(Item *);//If false, backpack broke


        void DropItemToTile(std::weak_ptr<BaseTile> tile_pointer);

        Item *get_item(const std::string &item_name) override;

        void Display_contents();

        virtual double get_weight() override;

        virtual double get_volume() override;
    };
}


#endif //WIFFWUFF_CONTAINER_H
