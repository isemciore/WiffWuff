//
// Created by erik on 2015-11-10.
//

#ifndef WIFFWUFF_BASE_TILE_H
#define WIFFWUFF_BASE_TILE_H
#include <memory>
#include <map>
#include "../character/baseunit.h"
#include "../stuff/Item.h"

namespace wumpus_game {
    class BaseUnit;
    
    class BaseTile {
    protected:

        int tile_id_;
        std::map<std::string,std::shared_ptr<BaseUnit>> map_of_char_in_tile_;
        std::map<std::string,std::weak_ptr<BaseTile>> map_of_neighbour_tile_;
        std::multimap<std::string, Item *> map_of_items_in_tile_;
        const double damage_reduction_fct_ = 0.1;
        //debugging purp
        //NORTH EAST SOUTH WEST ORDER
        bool feaseable_direction[4] = {false};
        bool wumpus_is_here = false;
        bool player_is_here = false;
        bool AddCharToTile(std::shared_ptr<BaseUnit>);//"Force add unit"


    public:
        friend class GameMaster;
        typedef std::map<std::string,std::weak_ptr<BaseTile>> neighbour_map_type;
        typedef std::map<std::string,std::shared_ptr<BaseUnit>> character_map_type;
        typedef std::multimap<std::string, Item *> item_map_type;

        BaseTile(const int &);
        BaseTile(const BaseTile &) = delete;
        ~BaseTile();

        int get_tile_id();

        std::map<std::string, std::weak_ptr<BaseTile>> get_neigbour_map();

        character_map_type get_character_in_room();

        virtual void PrintPlayerOptionAndInformation();
        virtual void PrintTileDependentInformation() = 0;

        virtual std::pair<bool, std::string> unit_can_attack_here(std::string unit_name) = 0;

        virtual double attack_damage_mod_tile(const std::string &unit_name) = 0;

        bool is_wumpus_here();

        bool is_player_here();

        virtual bool AttackAction(const std::string &attacker, const std::string &defendent);

        virtual bool EnterCharacter(std::shared_ptr<BaseUnit>);

        //Check if unit is sallowed
        virtual bool MoveCharacter(const std::string &name, const std::string &direction);

        virtual bool Exit(const std::string &name);

        Item * GetItemPointer(const std::string & item_name);
        virtual bool AddItem(Item *);


        virtual bool shoot_able_from_room();

    };

}

#endif //WIFFWUFF_BASE_TILE_H
