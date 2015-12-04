//
// Created by erik on 2015-11-10.
//

#ifndef WIFFWUFF_BASE_UNIT_H
#define WIFFWUFF_BASE_UNIT_H

#include <memory>
#include "../enviroment/basetile.h"
#include "../stuff/Consumable.h"
#include <vector>

namespace wumpus_game {
    class BaseTile;

    class BaseUnit {
        friend class Consumable;
    protected:
        std::weak_ptr<BaseTile> location_tile_pointer_;
        std::string unit_name_;
        bool can_attack_in_water_ = false;

        int attack_damage = 20;
        int current_health = 100;
        int current_mana = 80;
        /*
        typedef bool ()
        typedef std::pair<bool,std::string> (game_map::* MFP)(std::shared_ptr<unit> src, std::vector<std::string> argsCmd);
        std::map<std::string, MFP> mapofMFP;*/

    public:
        BaseUnit(const std::string name,const std::weak_ptr<BaseTile> initPosition);
        BaseUnit(const BaseUnit &) = delete; //No copy of unit, due too unique name
        virtual ~BaseUnit();

        void SetTilePointer(std::weak_ptr<BaseTile> baseTp);
        virtual void PerformAction() = 0;
        std::weak_ptr<BaseTile> GetUnitLocation(){return location_tile_pointer_;};

        virtual int get_attack_damage();
        virtual bool RecieveDamage(int damage_taken_b4_reduction);

        bool Travel(const std::vector<std::string> &vec_direction);
        bool Attack(const std::vector<std::string> &vec_command_argument);
        std::string get_unit_name();
        int get_current_unit_hp(){return current_health;}
        int get_current_unit_mana(){return current_mana;}
        virtual bool attack_in_water();

    };

}

#endif //WIFFWUFF_BASE_UNIT_H
