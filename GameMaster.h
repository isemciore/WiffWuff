//
// Created by erik on 2015-11-10.
//

#ifndef WIFFWUFF_GAME_MASTER_H
#define WIFFWUFF_GAME_MASTER_H

#include <memory>
#include "gameSave.h"
#include "character/BaseUnit.h"
#include <map>
#include <vector>
#include "character/player_ctrl.h"
namespace wumpus_game {

    class GameMaster {
        //typedef std::pair<bool ,std::string>(player_ctrl::* player_member_function_ptr)(std::vector<std::string>);
        //std::map<std::size_t,player_member_function_ptr> map_player_member_function_ptr;
        typedef std::map<std::string,std::weak_ptr<BaseUnit>>::iterator unit_iterator_type;
        typedef std::pair<std::string,std::weak_ptr<BaseUnit>> string_tile_pair;

    private:
        std::map<std::string,std::weak_ptr<BaseUnit>> map_str_to_unitptr_;
        std::map<std::size_t,std::shared_ptr<BaseTile>> map_tile_id_to_tileptr_;
        std::shared_ptr<player_ctrl> player_ptr;
        std::size_t turn_number_;
        std::size_t tile_counter_ = 0;
        std::size_t unit_counter_ = 0;


    public:
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

        void AddUnit(const std::shared_ptr<BaseUnit> &, const std::size_t & tile_id);
        void AddUnit(const std::string& unit_type_name);
        void AddTile(const std::string& tile_type_name);
        void RemoveTile(const std::size_t& tile_id);

        void InitPrintStoryAndQuestion();
        void InitTurnMessages(std::size_t turn_no);
        void EndGameMessage();

    };//

}

#endif //WIFFWUFF_GAME_MASTER_H
