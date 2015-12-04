//
// Created by ezhang on 2015-11-26.
//


#include <iostream>
#include "tile_escape_win.h"

std::pair<bool, std::string> wumpus_game::Tile_escape_win::unit_can_attack_here(std::string unit_name) {
    return std::make_pair(true, "-");
}

wumpus_game::Tile_escape_win::Tile_escape_win(const int &tile_id)
        : BaseTile(tile_id){

}

bool wumpus_game::Tile_escape_win::EnterCharacter(std::shared_ptr<BaseUnit> ptr) {
    if(ptr->get_unit_name()!="Meep"){
        return false;
    }

    std::cout << "with your new fresh nightvision googles you can see around in this room and you see"
                         "a ladder in the middle of the room with a bright light shining down the case \n";
    AddCharToTile(ptr);
    return true;
}

bool wumpus_game::Tile_escape_win::MoveCharacter(const std::string &name, const std::string &direction) {
    std::cout << "you dont want to dive deeper into the mess \n";
    return false;
}

void wumpus_game::Tile_escape_win::PrintTileDependentInformation() {

}

void wumpus_game::Tile_escape_win::finish_game() {

}

void wumpus_game::Tile_escape_win::PrintPlayerOptionAndInformation() {
    std::cout << "You can smell escape, perhaps you should follow the light?\n";
    std::cout << "hint*, climb ladder\n";
}

double wumpus_game::Tile_escape_win::attack_damage_mod_tile(const std::string &unit_name) {
    return 1;
}
