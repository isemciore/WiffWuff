//
// Created by erik on 2015-11-10.
//

#ifndef WIFFWUFF_GAME_MASTER_H
#define WIFFWUFF_GAME_MASTER_H

#include <memory>
#include "gameSave.h"
#include "character/base_unit.h"
#include <map>

namespace wumpus_game {

    class GameMaster {
    private:
        std::map<std::string,std::weak_ptr<base_unit>> map_str_to_unitptr_;
        std::map<std::size_t,std::shared_ptr<base_tile>> map_tile_id_to_tileptr_;

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

        void AddUnit(const std::shared_ptr<base_unit> &, const std::size_t & tile_id);
        void AddUnit(const std::string& unit_type_name);
        void AddTile(const std::string& tile_type_name);
        void RemoveTile(const std::size_t& tile_id);


    };//

}

#endif //WIFFWUFF_GAME_MASTER_H
