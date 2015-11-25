//
// Created by erik on 2015-11-10.
//

#ifndef WIFFWUFF_GAME_MASTER_H
#define WIFFWUFF_GAME_MASTER_H

#include <memory>
#include "gamesave.h"
#include "character/baseunit.h"
#include <map>
#include <vector>
#include "character/PlayerCtrl.h"
#include "character/wumpus.h"

namespace wumpus_game {

    class GameMaster {
        //typedef std::pair<bool ,std::string>(PlayerCtrl::* player_member_function_ptr)(std::vector<std::string>);
        //std::map<std::size_t,player_member_function_ptr> map_player_member_function_ptr;
    private:
        std::map<std::string,std::weak_ptr<BaseUnit>> map_str_to_unitptr_;
        //std::vector<std::shared_ptr<BaseTile>> vector_of_tileptr_;
        std::map<std::size_t, std::shared_ptr<BaseTile>> map_int_to_tileptr_;
        std::shared_ptr<PlayerCtrl> player_ptr_;
        //else wumpus disapears?
        std::pair<bool,std::weak_ptr<Wumpus>> wumpus_ptr_;  //trigger dead wumpus event once
        std::size_t turn_number_;
        std::size_t tile_counter_ = 0;
        std::size_t unit_counter_ = 0;


    public:
        typedef std::map<std::size_t, std::shared_ptr<BaseTile>> map_tileptr_type;
        typedef std::map<std::string,std::weak_ptr<BaseUnit>>::iterator unit_iterator_type;
        typedef std::pair<std::string,std::weak_ptr<BaseUnit>> string_tile_pair;

        GameMaster();
        GameMaster(const gameSave & saveFile);
        ~GameMaster();
        GameMaster(const GameMaster &) = delete;

        void GameStart();


    private:
        void EventDay0();
        void EventNewSpawns();
        void EventDestroyTile();


        void SaveGame();

        void SetMapSquare(const std::size_t & num_tile_width);

        void AddUnit(const std::string& unit_type_name, const std::size_t location_id);
        void AddTile(const std::string& tile_type_name);
        void RemoveTile(const std::size_t& tile_id);

        void AddItem(std::string new_item_name, double new_item_weight, double new_item_volume, int dest);
        void AddContainer(std::string new_container_name, double new_cont_wei_cap, double new_cont_vol_cap, int dest);

        void AddConsumable(std::string item_name, int destination_id);
        void AddConsumable(std::string item_name, double new_item_weight,double new_item_volume,double delta_hp, double delta_mana, int dest);

        void InitPrintStoryAndQuestion();
        void InitTurnMessages(std::size_t turn_no);
        void EndGameMessage();

        void EventSwapGoalTile();


        void InitialItemDrop();

        void AddItem(Item *item_type_ptr, int dest);
    };//

}

#endif //WIFFWUFF_GAME_MASTER_H
