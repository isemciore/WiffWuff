//
// Created by ezhang on 2015-11-13.
//

#include "consumable.h"

std::pair<int, int> wumpus_game::consumable::consume() {
    return std::make_pair(hp_mod_,mana_mod_);
}

wumpus_game::consumable::consumable(std::string item_name, int weight, int volume, int delta_hp, int delta_mana)
    : item(item_name,weight,volume)
    , hp_mod_(delta_hp)
    , mana_mod_(delta_mana){
}
