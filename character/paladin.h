//
// Created by ezhang on 2015-11-14.
//

#ifndef WIFFWUFF_PALADIN_H
#define WIFFWUFF_PALADIN_H


#include "player_ctrl.h"

namespace wumpus_game {
    class Paladin : public player_ctrl{
    public:
        typedef bool(Paladin::* string_to_member_function_ptr)(std::vector<std::string> user_input_argument);
        std::map<std::string, string_to_member_function_ptr> map_of_member_action;

        using player_ctrl::player_ctrl;
        Paladin(std::string name, std::weak_ptr<BaseTile> init_pos);


        virtual void PerformAction();
    };
}


#endif //WIFFWUFF_PALADIN_H
