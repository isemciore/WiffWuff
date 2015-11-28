//
// Created by ezhang on 2015-11-14.
//

#include "turtle.h"


wumpus_game::Turtle::Turtle(std::string name, std::weak_ptr<BaseTile> initPosition)
    : Npc(name,initPosition){
    can_attack_in_water_ = true;
}
