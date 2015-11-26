//
// Created by ezhang on 2015-11-26.
//

#include <iostream>
#include "tile_escape_win.h"

wumpus_game::Tile_escape_win::Tile_escape_win(std::size_t tile_id)
        : BaseTile(tile_id){

}

bool wumpus_game::Tile_escape_win::enter(std::shared_ptr<BaseUnit> ptr){
    if(ptr->get_unit_name()!="Meep"){
        return false;
    }

    std::cout << "with your new fresh nightvision googles you can see around in this room and you see"
                         "a ladder in the middle of the room with a bright light shining down the case \n";
    AddCharToTile(ptr);
    return true;
}

bool wumpus_game::Tile_escape_win::move_char(std::string name, std::string direction) {
    std::cout << "you dont want to dive deeper into the mess \n";
    return false;
}

void wumpus_game::Tile_escape_win::PrintTileDependentInformation() {

}

void wumpus_game::Tile_escape_win::finish_game() {

}
