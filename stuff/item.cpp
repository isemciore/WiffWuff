//
// Created by ezhang on 2015-11-13.
//

#include "item.h"

wumpus_game::item::~item() {

}

wumpus_game::item::item(std::string item_name, double weight, double volume)
    : item_name_(item_name)
    , weight_(weight)
    , volume_(volume){

}

int wumpus_game::item::get_volume() {
    return volume_;
}

std::string wumpus_game::item::get_name() {
    return item_name_;
}

int wumpus_game::item::get_weight() {
    return weight_;
}
