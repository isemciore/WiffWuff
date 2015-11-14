//
// Created by erik on 2015-11-10.
//

#ifndef WIFFWUFF_BASE_UNIT_H
#define WIFFWUFF_BASE_UNIT_H

#include <memory>
#include "../enviroment/BaseTile.h"
#include <vector>

namespace wumpus_game {
    class BaseTile;

    class BaseUnit {
    protected:
        std::weak_ptr<BaseTile> location_tile_pointer_;
        std::string unit_name_;

        typedef bool(BaseUnit::* string_to_member_function_ptr)(std::vector<std::string> user_input_argument);
        std::map<std::string, string_to_member_function_ptr> map_of_member_action;
        /*
        typedef bool ()
        typedef std::pair<bool,std::string> (game_map::* MFP)(std::shared_ptr<unit> src, std::vector<std::string> argsCmd);
        std::map<std::string, MFP> mapofMFP;*/

    public:
        BaseUnit(std::string name, std::weak_ptr<BaseTile> initPosition);
        BaseUnit(const BaseUnit &) = delete; //No copy of unit, due too unique name
        ~BaseUnit();

        void SetTilePointer(std::weak_ptr<BaseTile> baseTp);
        virtual void PerformAction() = 0;
        std::weak_ptr<BaseTile> GetUnitLocation() {
            return location_tile_pointer_;
        }


        bool travel(std::string direction);

        std::string get_unit_name(){return unit_name_;};



    };

}

#endif //WIFFWUFF_BASE_UNIT_H
