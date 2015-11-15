//
// Created by erik on 2015-11-10.
//

#include <iostream>
#include "basetile.h"


wumpus_game::BaseTile::BaseTile(const wumpus_game::BaseTile &tile) {

}

wumpus_game::BaseTile::~BaseTile() {

}



wumpus_game::BaseTile::BaseTile(size_t t)
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
    if(target_pair_it == map_of_neighbour_tile_.end()){
        std::cout << "direction does not exist\n";
        return false;
    }


    bool enter_success =   target_pair_it->second.lock()->enter(src_ptr);
    if(!enter_success){
        std::cout << "could not enter\n";
        return false;
    }
    std::cout << "entering next room\n";
    src_ptr->SetTilePointer(target_pair_it->second);
    this->exit(name);


    return true;
}

bool wumpus_game::BaseTile::exit(const std::string & name) {
    if(name=="Wumpus"){
        wumpus_is_here = false;
    }
    map_of_neighbour_tile_.erase(name);
    return true;
}

bool wumpus_game::BaseTile::enter(std::shared_ptr<wumpus_game::BaseUnit> ptr) {
    AddCharToTile(ptr);
    return true;
}

void wumpus_game::BaseTile::PrintPlayerOptionAndInformation() {
    for(auto neighbour_tile_pair: map_of_neighbour_tile_){
        if(neighbour_tile_pair.second.lock()->is_wumpus_here()){
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


}