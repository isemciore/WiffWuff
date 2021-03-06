//
// Created by ezhang on 2015-11-13.
//

#ifndef WIFFWUFF_PLAYER_CTRL_H
#define WIFFWUFF_PLAYER_CTRL_H

#include "baseunit.h"
#include "../stuff/container.h"

namespace wumpus_game {
    class PlayerCtrl : public BaseUnit {
    protected:
        Item * head_slot_ = nullptr;
        Item * right_hand_ = nullptr;
        Item * left_hand_ = nullptr;
        Item * back_ = nullptr;

        typedef std::map<std::string, Item **> map_of_item_slot_type;
        map_of_item_slot_type map_of_item_slot_;



    public:
        virtual ~PlayerCtrl();

        using BaseUnit::BaseUnit;
        PlayerCtrl(const std::string name,const std::weak_ptr<BaseTile> bstile);
        std::pair<bool,std::string> game_continue = std::make_pair(true,"empty");
        virtual void PerformAction() = 0;

        bool PickUpItem(const std::vector<std::string> &arguments);
        bool DropItem(const std::vector<std::string> &arguments);
        bool MoveItem(const std::vector<std::string> &arguments);//Check han d is free
        bool ClimbLadder(const std::vector<std::string> &arguments);
        bool ConsumeItem(const std::vector<std::string> &arguments);
        bool DisplayWield(const std::vector<std::string> &arguments);
    };
}

#endif //WIFFWUFF_PLAYER_CTRL_H
