//
// Created by ezhang on 2015-11-13.
//

#ifndef WIFFWUFF_ITEM_H
#define WIFFWUFF_ITEM_H
#include <string>

namespace wumpus_game {
    class item {
    protected:
        std::string item_name_;
        int weight_;
        int volume_;
    public:
        item(std::string item_name, int weight, int volume);
        item(const item&) = delete;
        ~item();
    };
}

#endif //WIFFWUFF_ITEM_H
