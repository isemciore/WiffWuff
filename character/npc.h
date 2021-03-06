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
        Npc(const std::string name,const std::weak_ptr<BaseTile> initPosition);
        using BaseUnit::BaseUnit;

        virtual void PerformAction();
        void setAggresiveMode(bool aggresive){aggresive_unit = aggresive;}
    };
}

#endif //WIFFWUFF_NPC_H
