//
// Created by ezhang on 2015-11-13.
//

#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include "player_ctrl.h"

void wumpus_game::player_ctrl::PerformAction() {
    std::string user_input_args;
//http://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
    getline(std::cin,user_input_args);
    std::stringstream ss(user_input_args);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> vectorize_user_input(begin,end);














}
