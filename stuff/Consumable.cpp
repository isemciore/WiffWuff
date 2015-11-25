//
// Created by ezhang on 2015-11-13.
//

#include "Consumable.h"

std::pair<int, int> wumpus_game::Consumable::consume() {
    return std::make_pair(hp_mod_,mana_mod_);
}

wumpus_game::Consumable::Consumable(std::string item_name, double weight, double volume, double delta_hp, double delta_mana)
    : Item(item_name,weight,volume)
    , hp_mod_(delta_hp)
    , mana_mod_(delta_mana){
}
