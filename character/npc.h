//
// Created by ezhang on 2015-11-13.
//

#ifndef WIFFWUFF_NPC_H
#define WIFFWUFF_NPC_H

#include "baseunit.h"

namespace wumpus_game {
    class Npc : public BaseUnit {
    protected:
        bool aggresive_unit = false;
    public:
        Npc(std::string name, std::weak_ptr<BaseTile> initPosition);
        using BaseUnit::BaseUnit;

        virtual void PerformAction() = 0;
    };
}

#endif //WIFFWUFF_NPC_H
