//
// Created by ezhang on 2015-11-13.
//

#include <iostream>
#include "npc.h"

wumpus_game::Npc::Npc(const std::string name, const std::weak_ptr<BaseTile> initPosition)
    : BaseUnit(name,initPosition){

}

void wumpus_game::Npc::PerformAction() {


    if(location_tile_pointer_.lock()->is_player_here() && aggresive_unit){
        location_tile_pointer_.lock()->AttackAction(unit_name_, "Meep");
    } else if (current_health > 50) {
        int dir = rand()%4;
        if (dir == 0) location_tile_pointer_.lock()->MoveCharacter(unit_name_, "north");
        else if (dir == 1) location_tile_pointer_.lock()->MoveCharacter(unit_name_, "east");
        else if (dir == 2) location_tile_pointer_.lock()->MoveCharacter(unit_name_, "west");
        else location_tile_pointer_.lock()->MoveCharacter(unit_name_, "south");

        if(location_tile_pointer_.lock()->is_player_here() && aggresive_unit){
            location_tile_pointer_.lock()->AttackAction(unit_name_, "Meep");
        }
    }
}
