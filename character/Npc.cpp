//
// Created by ezhang on 2015-11-13.
//

#include "Npc.h"

wumpus_game::Npc::Npc(std::string name, std::weak_ptr<BaseTile> initPosition)
    : BaseUnit(name,initPosition){

}
