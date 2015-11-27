//
// Created by ezhang on 2015-11-27.
//

#ifndef WIFFWUFF_SORCERER_H
#define WIFFWUFF_SORCERER_H


#include "PlayerCtrl.h"

namespace wumpus_game {
    class Sorcerer : public PlayerCtrl{
    public:
        typedef bool(Sorcerer::* member_function_ptr_type)(std::vector<std::string> user_input_argument);
        typedef std::map<std::string, member_function_ptr_type> map_of_member_action_type;
        map_of_member_action_type map_of_member_action_;
        using PlayerCtrl::PlayerCtrl;
        Sorcerer(std::string name, std::weak_ptr<BaseTile> init_pos);


        virtual void PerformAction() override;

        bool Cast_spell(std::vector<std::string> input_cmds);
    };
}


#endif //WIFFWUFF_SORCERER_H
