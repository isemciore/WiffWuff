//
// Created by erik on 2015-11-10.
//

#include <iostream>
#include "BaseTile.h"
#include "../character/BaseUnit.h"


wumpus_game::BaseTile::BaseTile(const wumpus_game::BaseTile &tile) {

}

wumpus_game::BaseTile::~BaseTile() {

}

void wumpus_game::BaseTile::SetUnitPointer(std::weak_ptr<BaseUnit> baseUp) {
    _baseUp_ = baseUp;
}



wumpus_game::BaseTile::BaseTile(size_t t)
    : tile_id_(t)
{
}

bool wumpus_game::BaseTile::AddCharToTile(std::shared_ptr<wumpus_game::BaseUnit> ptr) {
    std::string unit_name = ptr->get_unit_name();
    map_of_char_in_tile_.insert(std::make_pair(unit_name,ptr));
    return false;
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
    }
    std::cout << "entering next room\n";
    src_ptr->SetTilePointer(target_pair_it->second);
    this->exit(name);
}

bool wumpus_game::BaseTile::exit(const std::string & name) {
    map_of_neighbour_tile_.erase(name);
    return true;
}

bool wumpus_game::BaseTile::enter(std::shared_ptr<wumpus_game::BaseUnit> ptr) {
    AddCharToTile(ptr);
    return true;
}

