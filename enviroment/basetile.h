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

        std::size_t tile_id_;
        std::map<std::string,std::shared_ptr<BaseUnit>> map_of_char_in_tile_;
        std::map<std::string,std::weak_ptr<BaseTile>> map_of_neighbour_tile_;
        std::multimap<std::string, Item *> map_of_items_in_tile_;

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
        BaseTile(std::size_t);
        BaseTile(const BaseTile &);
        ~BaseTile();

        void SetUnitPointer(std::weak_ptr<BaseUnit> baseUp);
        std::size_t get_tile_id();
        std::map<std::string,std::weak_ptr<BaseTile>> get_neigbour_map() {return map_of_neighbour_tile_;}
        character_map_type get_character_in_room(){return map_of_char_in_tile_;}

        void PrintPlayerOptionAndInformation();
        virtual void PrintTileDependentInformation() = 0;

        bool is_wumpus_here(){ return wumpus_is_here;}
        bool is_player_here(){ return player_is_here;}
        virtual bool attack_action(std::string attacker, std::string defendent);
        virtual bool enter(std::shared_ptr<BaseUnit>);//Check if unit is sallowed
        virtual bool move_char(std::string name, std::string direction);
        virtual bool exit(const std::string & name);

        Item * GetItemPointer(const std::string & item_name);
        virtual bool AddItem(Item *);


        virtual bool shoot_able_from_room(){return true;};

    };

}

#endif //WIFFWUFF_BASE_TILE_H
