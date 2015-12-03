//
// Created by erik on 2015-11-13.
//

#include <iostream>
#include "tile_ocean.h"



wumpus_game::TileOcean::TileOcean(std::size_t tile_id)
    : BaseTile(tile_id){
    feaseable_direction[0] = true;
    feaseable_direction[1] = true;
    feaseable_direction[2] = true;
    feaseable_direction[3] = true;

}

std::pair<bool, std::string> wumpus_game::TileOcean::unit_can_attack_here(std::string unit_name) {
    auto unit_pair_iterator = map_of_char_in_tile_.find(unit_name);
    if (!unit_pair_iterator->second->attack_in_water()){
        if (unit_name=="Meep"){
        }
        return std::make_pair(false, "water");
    }
    return std::make_pair(true, "-");
}

void wumpus_game::TileOcean::PrintTileDependentInformation() {
    std::cout << "You enter a waterfilled room and cannot attack in this room\n";
}

bool wumpus_game::TileOcean::AddItem(wumpus_game::Item *item) {
    double item_density = ((double) item->get_weight())/((double) item->get_volume());
    if(item_density > 1){
        std::cout << item->get_name()<<" sinks to the bottom (density > 1)\n";
        delete item;
        return false;
    }
    map_of_items_in_tile_.insert(std::make_pair(item->get_name(),item));
    return true;
}
