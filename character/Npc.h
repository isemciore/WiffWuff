//
// Created by ezhang on 2015-11-13.
//

#ifndef WIFFWUFF_NPC_H
#define WIFFWUFF_NPC_H

#include "BaseUnit.h"

namespace wumpus_game {
    class Npc : public BaseUnit {
    protected:
        bool aggresive_unit = false;
    public:
        using BaseUnit::BaseUnit;

        virtual void PerformAction() = 0;
    };
}

#endif //WIFFWUFF_NPC_H
