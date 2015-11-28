//
// Created by ezhang on 2015-11-13.
//

#ifndef WIFFWUFF_ITEM_H
#define WIFFWUFF_ITEM_H
#include <string>

namespace wumpus_game {
    class Item {
    protected:
        const std::string item_name_;
        const double weight_;
        const double volume_;
    public:
        Item(const std::string &item_name, const double &weight,const double &volume);
        Item(const Item &) = delete;
        virtual ~Item();

        std::string get_name();

        virtual int get_weight();
        virtual int get_volume();

        virtual Item * get_item(std::string item_name); //delete denna
    };
}

#endif //WIFFWUFF_ITEM_H
