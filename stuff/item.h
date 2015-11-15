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
        double weight_;
        double volume_;
    public:
        item(std::string item_name, double weight, double volume);
        item(const item&) = delete;
        ~item();

        std::string get_name();
        int get_weight();
        int get_volume();
    };
}

#endif //WIFFWUFF_ITEM_H
