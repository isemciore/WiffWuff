//
// Created by ezhang on 2015-11-14.
//

#include "wumpus.h"

void wumpus_game::Wumpus::PerformAction() {

}

wumpus_game::Wumpus::Wumpus(const std::string name,const std::weak_ptr<BaseTile> initPosition)
    : Npc(name,initPosition){
    aggresive_unit = true;
}
