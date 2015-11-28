//
// Created by ezhang on 2015-11-13.
//

#include <iostream>
#include "container.h"

wumpus_game::container::container(std::string name, double holdWeight, double holdVolume)
    : Item(name, 0.0,0.0)
    , k_capacity_hold_weight_(holdWeight)
    , k_capacity_hold_volume_(holdVolume)
{

}

bool wumpus_game::container::AddItem(wumpus_game::Item *item) {
    internal_extra_weight += item->get_weight();
    internal_extra_volume += item->get_volume();
    item_container.insert(std::make_pair(item->get_name(), item));

    if(weight_ > k_capacity_hold_volume_){
        std::cout << "Backpack breaks due to too big Item \n";
        return false;
    }
    if(volume_>k_capacity_hold_volume_){
        std::cout << "Backpack weights too much and breaks \n";
        return false;
    }
    return true;
}

wumpus_game::Item *wumpus_game::container::get_item(std::string item_name) {
    if (item_name == item_name_){
        return this;
    }
    std::map<std::string, Item *>::iterator item_iterator = item_container.find(item_name);
    if(item_iterator == item_container.end()){
        std::cout << "cannot find Item in backpack \n";
        return nullptr;
    }
    Item * ptr_to_item = item_iterator->second;
    item_container.erase(item_iterator);
    return ptr_to_item;
}


void wumpus_game::container::DropItemToTile(std::weak_ptr<BaseTile> tile_pointer) {
    item_container_iterator first_item = item_container.begin();
    item_container_iterator last_item  = item_container.end();

    while(first_item != last_item){
        tile_pointer.lock()->AddItem(first_item->second);
        first_item = item_container.erase(first_item);
    }
}

void wumpus_game::container::Display_contents() {
    for(auto & item1 : item_container){
        std::cout << item1.second->get_name()<< ", ";
    }
}

wumpus_game::container::~container() {
    std::map<std::string, Item *>::iterator itr_begin = item_container.begin();
    std::map<std::string, Item *>::iterator itr_end = item_container.end();
    while(itr_begin != itr_end){
        if (itr_begin->second != nullptr) {
            delete itr_begin->second;
        }
        itr_begin = item_container.erase(itr_begin);
    }
}

int wumpus_game::container::get_weight() {
    return weight_+internal_extra_weight;
}

int wumpus_game::container::get_volume() {
    return volume_+internal_extra_volume;
}
