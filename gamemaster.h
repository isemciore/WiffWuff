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
        int desutrction_order_ [25] = {24,23,22,21,20,15,10,5,0,1,2,3,4,9,14,
                                          19,18,17,16,11,6,7,8,13};
        std::size_t tile_destruction_number_ = 0;
        const std::size_t k_tile_max_destruction_num = 23;

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
        bool EventDestroyTile();


        void SaveGame();

        void SetMapSquare(const std::size_t & num_tile_width);

        void AddUnit(const std::string& unit_type_name, const std::size_t location_id);
        void AddTile(const std::string& tile_type_name);
        bool RemoveTile(const int & tile_id);

        void AddItem(const std::string &new_item_name, const double &new_item_weight,
                     const double &new_item_volume, const int &dest);

        void AddContainer(const std::string &new_container_name, const double &new_cont_wei_cap,
                          const double &new_cont_vol_cap, const int &dest);

        void AddConsumable(const std::string &item_name, const int &destination_id);

        void AddConsumable(const std::string &item_name, const double &new_item_weight, const double &new_item_volume,
                           const double &delta_hp, const double &delta_mana, const int &dest);

        void InitPrintStoryAndQuestion();

        void InitTurnMessages(const std::size_t &turn_no);
        void EndGameMessage();

        void EventSwapGoalTile();

        void AttachNeighbour(map_tileptr_type::iterator room_ptr,const std::size_t &num_tile_width);
        void InitialItemDrop();

        void AddItem(Item *item_type_ptr, const int &dest);

        void AddItem(const std::string &itemname, const int &dest);
    };//

}

#endif //WIFFWUFF_GAME_MASTER_H
