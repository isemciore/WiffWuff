//
// Created by ezhang on 2015-11-14.
//

#include "paladin.h"
#include <iostream>
#include <sstream>
#include <iterator>

wumpus_game::Paladin::Paladin(std::string name, std::weak_ptr<BaseTile> init_pos)
    : player_ctrl(name, init_pos){
    map_of_member_action.insert(std::make_pair("Travel", &BaseUnit::Travel));
    map_of_member_action.insert(std::make_pair("Attack", &BaseUnit::Attack));

}

void wumpus_game::Paladin::PerformAction() {
    std::string user_input_args;
//http://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
    getline(std::cin,user_input_args);
    std::stringstream ss(user_input_args);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vectorize_user_input(begin,end);



}
