//
// Created by ezhang on 2015-11-13.
//

#ifndef WIFFWUFF_CONTAINER_H
#define WIFFWUFF_CONTAINER_H


#include "item.h"

namespace wumpus_game {
    class container : public item{
        int holdWeight_;
        int holdVolume_;
    public:
        container(std::string name, int weight, int volume, int holdWeight, int holdVolume);

    };
}


#endif //WIFFWUFF_CONTAINER_H
