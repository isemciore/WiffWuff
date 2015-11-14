//
// Created by ezhang on 2015-11-14.
//

#ifndef WIFFWUFF_WUMPUS_H
#define WIFFWUFF_WUMPUS_H


#include "Npc.h"

namespace wumpus_game {
    class Wumpus : public Npc {
    public:
        Wumpus(std::string name, std::weak_ptr<BaseTile> initPosition);
        using Npc::Npc;
        using Npc::BaseUnit;

        virtual void PerformAction();
    };
}


#endif //WIFFWUFF_WUMPUS_H
