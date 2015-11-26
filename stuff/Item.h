//
// Created by ezhang on 2015-11-13.
//

#ifndef WIFFWUFF_ITEM_H
#define WIFFWUFF_ITEM_H
#include <string>

namespace wumpus_game {
    class Item {
    protected:
        std::string item_name_;
        double weight_;
        double volume_;
    public:
        Item(std::string item_name, double weight, double volume);
        Item(const Item &) = delete;
        ~Item();

        std::string get_name();

        int get_weight();
        int get_volume();

        virtual Item * get_item(std::string item_name); //delete denna
    };
}

#endif //WIFFWUFF_ITEM_H
