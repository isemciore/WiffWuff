//
// Created by ezhang on 2015-11-13.
//

#include <iostream>
#include "npc.h"

wumpus_game::Npc::Npc(std::string name, std::weak_ptr<BaseTile> initPosition)
    : BaseUnit(name,initPosition){

}

void wumpus_game::Npc::PerformAction() {
    if(unit_name_ == "mean_turtle3"){
        std::cout << "mean turtle turn\n";
        std::cout << location_tile_pointer_.lock()->get_tile_id() << "\n";
    }

    if(location_tile_pointer_.lock()->is_player_here() && aggresive_unit){
        location_tile_pointer_.lock()->attack_action(unit_name_,"Meep");
    } else{
        int dir = rand()%4;
        if(dir == 0) location_tile_pointer_.lock()->move_char(unit_name_,"north");
        else if(dir==1) location_tile_pointer_.lock()->move_char(unit_name_,"east");
        else if(dir==2) location_tile_pointer_.lock()->move_char(unit_name_,"west");
        else location_tile_pointer_.lock()->move_char(unit_name_,"south");

        if(location_tile_pointer_.lock()->is_player_here() && aggresive_unit){
            location_tile_pointer_.lock()->attack_action(unit_name_,"Meep");
        }
    }

    if(unit_name_ == "mean_turtle3"){
        std::cout << "mean turtle turn\n";
        std::cout << location_tile_pointer_.lock()->get_tile_id() << "\n";
    }
}
