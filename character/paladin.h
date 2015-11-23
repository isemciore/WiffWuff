//
// Created by ezhang on 2015-11-14.
//

#ifndef WIFFWUFF_PALADIN_H
#define WIFFWUFF_PALADIN_H


#include "PlayerCtrl.h"

namespace wumpus_game {
    class Paladin : public PlayerCtrl {
    public:
        typedef bool(Paladin::* member_function_ptr_type)(std::vector<std::string> user_input_argument);
        typedef std::map<std::string, member_function_ptr_type> map_of_member_action_type;
        map_of_member_action_type map_of_member_action_;

        using PlayerCtrl::PlayerCtrl;
        Paladin(std::string name, std::weak_ptr<BaseTile> init_pos);


        virtual void PerformAction();

        bool Shoot(std::vector<std::string> input_cmds);

    };
}


#endif //WIFFWUFF_PALADIN_H
