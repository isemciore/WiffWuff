//
// Created by ezhang on 2015-11-14.
//

#ifndef WIFFWUFF_PALADIN_H
#define WIFFWUFF_PALADIN_H


#include "player_ctrl.h"

namespace wumpus_game {
    class Paladin : public player_ctrl{
    public:
        using player_ctrl::player_ctrl;
        Paladin(std::string name, std::weak_ptr<BaseTile> init_pos) : player_ctrl(name, init_pos){}


    };
}


#endif //WIFFWUFF_PALADIN_H
