//
// Created by ezhang on 2015-11-13.
//

#include "item.h"

wumpus_game::item::~item() {

}

wumpus_game::item::item(std::string item_name, int weight, int volume)
    : item_name_(item_name)
    , weight_(weight)
    , volume_(volume){

}
