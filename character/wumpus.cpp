//
// Created by ezhang on 2015-11-14.
//

#include "wumpus.h"

void wumpus_game::Wumpus::PerformAction() { //OVERIDE SO WUMPUS CANNOT MOVE
    /*if(location_tile_pointer_.lock()->is_player_here() && aggresive_unit){
        location_tile_pointer_.lock()->attack_action(unit_name_,"Meep");
    }*/
}

wumpus_game::Wumpus::Wumpus(std::string name, std::weak_ptr<BaseTile> initPosition)
    : Npc(name,initPosition){
    aggresive_unit = true;
    attack_damage = 10000;
}
