//
// Created by ezhang on 2015-11-13.
//

#include "Item.h"

wumpus_game::Item::~Item() {

}

wumpus_game::Item::Item(std::string item_name, double weight, double volume)
    : item_name_(item_name)
    , weight_(weight)
    , volume_(volume){

}

int wumpus_game::Item::get_volume() {
    return volume_;
}

std::string wumpus_game::Item::get_name() {
    return item_name_;
}

int wumpus_game::Item::get_weight() {
    return weight_;
}

wumpus_game::Item *wumpus_game::Item::get_item(std::string item_name) {
    if (!item_name_ .compare(item_name)){
        return this;
    }
    return nullptr;
}
