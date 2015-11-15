//
// Created by ezhang on 2015-11-13.
//

#include "container.h"

wumpus_game::container::container(std::string name, int weight, int volume, int holdWeight, int holdVolume)
    : item(name, weight,volume)
    , holdWeight_(holdWeight)
    , holdVolume_(holdVolume)
{

}
