//
// Created by ezhang on 2015-11-13.
//

#ifndef WIFFWUFF_CONSUMABLE_H
#define WIFFWUFF_CONSUMABLE_H


#include "Item.h"
#include "../character/baseunit.h"

namespace wumpus_game {
    class BaseUnit;
    class Consumable :public Item {
    private:
        const double hp_mod_;
        const double mana_mod_;
    public:
        Consumable(const std::string &item_name, const double &weight, const double &volume, const double &delta_hp,
                   const double &delta_mana);

        double get_delta_hp() { return hp_mod_; }

        //prob not used
        double get_delta_mana() { return mana_mod_; }

        void Consume(BaseUnit *);

    };
}


#endif //WIFFWUFF_CONSUMABLE_H
