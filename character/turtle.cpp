//
// Created by ezhang on 2015-11-14.
//

#include "turtle.h"


wumpus_game::Turtle::Turtle(const std::string name,const std::weak_ptr<BaseTile> initPosition)
    : Npc(name,initPosition){
    can_attack_in_water_ = true;
}
