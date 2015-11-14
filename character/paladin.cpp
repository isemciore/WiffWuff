//
// Created by ezhang on 2015-11-14.
//

#include "paladin.h"
#include <iostream>
#include <sstream>
#include <iterator>

wumpus_game::Paladin::Paladin(std::string name, std::weak_ptr<BaseTile> init_pos)
    : player_ctrl(name, init_pos){
    map_of_member_action_.insert(std::make_pair("Travel", &BaseUnit::Travel));
    map_of_member_action_.insert(std::make_pair("Attack", &BaseUnit::Attack));

}

void wumpus_game::Paladin::PerformAction() {
    std::string user_input_args;
//http://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
    bool event_success;
    //INIT TEXT AVAILABLE ACTION
    //AVAILABLE WALKING DIRECTION
    //INCASE SMELL OF WUMPUS
    while(true){
        event_success = false;
        getline(std::cin,user_input_args);
        std::stringstream ss(user_input_args);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vectorize_user_input(begin,end);
        vectorize_user_input.push_back("making sure this vector is non empty");


        map_of_member_action_type::iterator member_function_pair_iterator = map_of_member_action_.find(vectorize_user_input[0]);
        if(member_function_pair_iterator == map_of_member_action_.end()){
            std::cout << "unknown input\n";
        }else{
            member_function_ptr_type member_ptr = member_function_pair_iterator->second;

            event_success = ((*this).*member_ptr)(vectorize_user_input);
        }

        if(event_success && vectorize_user_input[0]=="Travel"){
            if(location_tile_pointer_.lock()->is_wumpus_here()){
                std::cout << "oh noo you walked into Wumpus\n";
                game_continue = std::make_pair(false,"eaten");
            }

            break;
        }
        if(event_success && vectorize_user_input[0]=="Climb"){
            game_continue = std::make_pair(false,"win");
            break;
        }
    }
}
