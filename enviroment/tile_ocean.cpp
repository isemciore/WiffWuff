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

bool wumpus_game::TileOcean::unit_can_attack_here(std::string unit_name) {
    auto unit_pair_iterator = map_of_char_in_tile_.find(unit_name);
    if (!unit_pair_iterator->second->attack_in_water()){
        if (unit_name=="Meep"){
            std::cout << " cannot attack while in water"<<"\n";
        }
        return false;
    }
    return true;
}

/*
bool wumpus_game::TileOcean::attack_action(std::string attacker, std::string defendent) {
    auto attacker_pair_iterator = map_of_char_in_tile_.find(attacker);
    //Fråga varför std::map<std::string,std::shared_ptr<BaseUnit>>::iterator
    //Ej fungerar, men fungerar ifall det skullev ara en map över weak_ptr

    if(!attacker_pair_iterator->second->attack_in_water()){
        std::cout << attacker << "cannot attack while swimming :( \n";
        return false;
    }
    auto defendent_pair_iterator = map_of_char_in_tile_.find(defendent);

    if(defendent_pair_iterator == map_of_char_in_tile_.end()){
        std::cout << "couldn't find target \n";
        return false;
    }

    if(attacker == defendent){
        std::cout << "Stop hitting you self\n";
        attacker_pair_iterator->second->RecieveDamage(10);
    }
    int atk_damage = attacker_pair_iterator->second->get_attack_damage();
    int def_damage = defendent_pair_iterator->second->get_attack_damage();

    std::cout << attacker << " attack with " << atk_damage << " damage ";
    bool defendent_alive = defendent_pair_iterator->second->RecieveDamage(atk_damage);
    if(defendent_alive){
        std::cout << defendent << " retaliates with "<< def_damage;
        attacker_pair_iterator->second->RecieveDamage(def_damage);
    } else{
        map_of_char_in_tile_.erase(defendent_pair_iterator);
    }
    return true;
}*/

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
