//
// Created by erik on 2015-11-10.
//

#include <iostream>
#include "basetile.h"



wumpus_game::BaseTile::~BaseTile() {
    item_map_type::iterator begin_itr = map_of_items_in_tile_.begin();
    item_map_type::iterator end_itr   = map_of_items_in_tile_.end();
    while(begin_itr != end_itr){
        if (begin_itr->second != nullptr){
            delete begin_itr->second;
        }
        begin_itr = map_of_items_in_tile_.erase(begin_itr);
    }
    character_map_type::iterator begin_character_itr = map_of_char_in_tile_.begin();
    character_map_type::iterator end_character_itr = map_of_char_in_tile_.end();
    while(begin_character_itr!=end_character_itr){
        /* //sharedpointer dont need delete
        if(begin_character_itr->second!= nullptr){
            delete begin_character_itr->second;
        }*/
        begin_character_itr = map_of_char_in_tile_.erase(begin_character_itr);
    }



}



wumpus_game::BaseTile::BaseTile(const size_t t)
    : tile_id_(t)
{
}

bool wumpus_game::BaseTile::AddCharToTile(std::shared_ptr<wumpus_game::BaseUnit> ptr) {
    std::string unit_name = ptr->get_unit_name();
    map_of_char_in_tile_.insert(std::make_pair(unit_name,ptr));

    if(ptr->get_unit_name() == "Wumpus")
    {wumpus_is_here = true;}
    return true;
}

std::size_t wumpus_game::BaseTile::get_tile_id() {
    return tile_id_;
}

bool wumpus_game::BaseTile::move_char(std::string name, std::string direction) {
    std::shared_ptr<BaseUnit> src_ptr = map_of_char_in_tile_.find(name)->second;

    neighbour_map_type::iterator target_pair_it = map_of_neighbour_tile_.find(direction);
    if(target_pair_it == map_of_neighbour_tile_.end() || target_pair_it->second.expired() ){
        if(name=="Meep"){
        std::cout << "direction does not exist\n";}
        return false;
    }


    bool enter_success =   target_pair_it->second.lock()->enter(src_ptr);
    if(!enter_success){
        if(name=="Meep") {
            std::cout << "could not enter\n";
        }
        return false;
    }
    if(name=="Meep") {
        std::cout << "entering next room\n";
    }
    src_ptr->SetTilePointer(target_pair_it->second);
    this->exit(name);


    return true;
}

bool wumpus_game::BaseTile::exit(const std::string & name) {
    if(name=="Wumpus"){
        wumpus_is_here = false;
    }
    if(name=="Meep"){
        wumpus_is_here = false;
    }
    map_of_char_in_tile_.erase(name);
    return true;
}

bool wumpus_game::BaseTile::enter(std::shared_ptr<wumpus_game::BaseUnit> ptr) {
    if(ptr->get_unit_name() == "Meep"){
        player_is_here = true;
    }
    if(ptr->get_unit_name() == "Wumpus"){
        wumpus_is_here = true;
    }
    AddCharToTile(ptr);
    return true;
}

void wumpus_game::BaseTile::PrintPlayerOptionAndInformation() {

    for(auto neighbour_tile_pair: map_of_neighbour_tile_){
        if(neighbour_tile_pair.second.expired()){
            map_of_neighbour_tile_.erase(neighbour_tile_pair.first);
        }else if(neighbour_tile_pair.second.lock()->is_wumpus_here()){
            std::cout << "You smell the scent of Wumpus nearby \n";
            std::cout << "easy mode : he is located to the "<< neighbour_tile_pair.first << "\n";
        }
    }

    for(auto &character : map_of_char_in_tile_){
        if(character.first != "Meep"){
            std::cout << character.first << " is here\n";
        }
    }
    std::cout << "Direction you can move is:\n";
    for(auto neighbour_tile_pair: map_of_neighbour_tile_){
        std::cout << neighbour_tile_pair.first << " ";
    }
    std::cout << "\n";
    if(map_of_items_in_tile_.size()>0){
        std::cout << "In this room you can find \n";
        for(auto& item : map_of_items_in_tile_){
            std::cout << item.first << ", ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";


}

bool wumpus_game::BaseTile::attack_action(std::string attacker, std::string defendent) {
    auto attacker_pair_iterator = map_of_char_in_tile_.find(attacker);
    //Fråga varför std::map<std::string,std::shared_ptr<BaseUnit>>::iterator
    //Ej fungerar, men fungerar ifall det skullev ara en map över weak_ptr

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
        std::cout << defendent << " retaliates with "<< def_damage<<" damage";
        attacker_pair_iterator->second->RecieveDamage(def_damage);
    } else{
        map_of_char_in_tile_.erase(defendent_pair_iterator);
    }
    return true;
}

wumpus_game::Item *wumpus_game::BaseTile::GetItemPointer(const std::string & item_name) {
    auto item_it =  map_of_items_in_tile_.find(item_name);
    if(item_it == map_of_items_in_tile_.end()){
        std::cout << "Cannot find Item \n";
        return nullptr;
    }
    Item * item_return = item_it->second;
    map_of_items_in_tile_.erase(item_it);

    return item_return;
}

bool wumpus_game::BaseTile::AddItem(wumpus_game::Item * item) {
    map_of_items_in_tile_.insert(std::make_pair(item->get_name(),item));
    return true;
}
