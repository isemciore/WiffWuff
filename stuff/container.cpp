//
// Created by ezhang on 2015-11-13.
//

#include <iostream>
#include "container.h"

wumpus_game::container::container(std::string name, double holdWeight, double holdVolume)
    : item(name, 0.0,0.0)
    , k_capacity_hold_weight_(holdWeight)
    , k_capacity_hold_volume_(holdVolume)
{

}

bool wumpus_game::container::AddItem(wumpus_game::item *item) {
    weight_ += item->get_weight();
    volume_ += item->get_volume();
    item_container.insert(std::make_pair(item->get_name(), item));

    if(weight_ > k_capacity_hold_volume_){
        std::cout << "Backpack breaks due to too big item \n";
        return false;
    }
    if(volume_>k_capacity_hold_volume_){
        std::cout << "Backpack weights too much and breaks \n";
        return false;
    }
    return true;
}

wumpus_game::item *wumpus_game::container::GetItem(std::string item_name) {
    std::map<std::string,item*>::iterator item_iterator = item_container.find(item_name);
    if(item_iterator == item_container.end()){
        std::cout << "cannot find item in backpack \n";
        return nullptr;
    }
    item* ptr_to_item = item_iterator->second;
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
