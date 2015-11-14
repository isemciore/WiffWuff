//
// Created by ezhang on 2015-11-13.
//

#ifndef WIFFWUFF_PLAYER_CTRL_H
#define WIFFWUFF_PLAYER_CTRL_H

#include "BaseUnit.h"

namespace wumpus_game {
    class player_ctrl : public BaseUnit {
    public:
        std::pair<bool,std::string> game_continue = std::make_pair(true,"empty");
    };
}

#endif //WIFFWUFF_PLAYER_CTRL_H
