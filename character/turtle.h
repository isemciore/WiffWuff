//
// Created by ezhang on 2015-11-14.
//

#ifndef WIFFWUFF_TURTLE_H
#define WIFFWUFF_TURTLE_H


#include "npc.h"

namespace wumpus_game {
    class Turtle :public Npc {
    public:
        Turtle(std::string name, std::weak_ptr<BaseTile> initPosition);
        using Npc::Npc;
        using Npc::BaseUnit;

        virtual void PerformAction();
    };
}


#endif //WIFFWUFF_TURTLE_H
