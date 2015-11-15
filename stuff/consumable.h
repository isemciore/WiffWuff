//
// Created by ezhang on 2015-11-13.
//

#ifndef WIFFWUFF_CONSUMABLE_H
#define WIFFWUFF_CONSUMABLE_H


#include "item.h"

namespace wumpus_game {
    class consumable :public item {
    private:
        int hp_mod_;
        int mana_mod_;
    public:
        consumable(std::string item_name, double weight, double volume, double delta_hp, double delta_mana);
        std::pair<int,int> consume();
    };
}


#endif //WIFFWUFF_CONSUMABLE_H
