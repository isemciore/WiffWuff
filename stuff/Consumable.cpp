//
// Created by ezhang on 2015-11-13.
//

#include <iostream>
#include "Consumable.h"

wumpus_game::Consumable::Consumable(const std::string &item_name, const double &weight, const double &volume,
                                    const double &delta_hp, const double &delta_mana)
    : Item(item_name,weight,volume)
    , hp_mod_(delta_hp)
    , mana_mod_(delta_mana){
}


void wumpus_game::Consumable::Consume(wumpus_game::BaseUnit *unit) {
    if (hp_mod_ > 0) {
        (*unit).current_health = unit->current_health + hp_mod_;
        std::cout << "you gain " << hp_mod_ << " and your current health " << unit->current_health << "\n";
    }
    if (mana_mod_ > 0) {
        unit->current_health = unit->current_mana + mana_mod_;
        std::cout << "you gain " << mana_mod_ << " and your current mana is " << unit->current_health << "\n";
    }
}
