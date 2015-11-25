//
// Created by ezhang on 2015-11-13.
//

#ifndef WIFFWUFF_CONSUMABLE_H
#define WIFFWUFF_CONSUMABLE_H


#include "Item.h"

namespace wumpus_game {
    class Consumable :public Item {
    private:
        int hp_mod_;
        int mana_mod_;
    public:
        Consumable(std::string item_name, double weight, double volume, double delta_hp, double delta_mana);
        int get_delta_hp(){return hp_mod_;}
        int get_delta_mana(){return mana_mod_;}
        std::pair<int,int> consume();
    };
}


#endif //WIFFWUFF_CONSUMABLE_H
