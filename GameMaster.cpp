//
// Created by erik on 2015-11-10.
//

#include <iostream>
#include "GameMaster.h"
#include "enviroment/TileOcean.h"
#include "character/paladin.h"
#include "character/turtle.h"

wumpus_game::GameMaster::GameMaster() {
    turn_number_ = 0;
}

void wumpus_game::GameMaster::GameStart() {

    unit_iterator_type unit_it_begin;
    unit_iterator_type unit_it_end;

    for(turn_number_; turn_number_<10;turn_number_++){
        if (turn_number_==0){
            EventDay0();
        turn_number_++;
        }
        InitTurnMessages(turn_number_);
        if (turn_number_%3){
            EventNewSpawns();
        }
        if (turn_number_%4){
            EventDestroyTile();
        }
        unit_it_begin = map_str_to_unitptr_.begin();
        unit_it_end = map_str_to_unitptr_.end();

        while ((unit_it_begin != unit_it_end) && unit_it_begin->second.expired()){
            unit_it_begin = map_str_to_unitptr_.erase(unit_it_begin);
        }
        while((unit_it_begin != unit_it_end) && (player_ptr_->game_continue.first)){
            unit_it_begin->second.lock()->PerformAction();
            while (unit_it_begin->second.expired()){
                unit_it_begin = map_str_to_unitptr_.erase(unit_it_begin);
            }
            unit_it_begin++;
        }

        if (!player_ptr_->game_continue.first){
            break;
        }

        if(wumpus_ptr_.second.expired() && wumpus_ptr_.first== true){
            wumpus_ptr_.first = false;
            EventSwapGoalTile();
        }
    }
    EndGameMessage();

}

wumpus_game::GameMaster::~GameMaster() {

}

void wumpus_game::GameMaster::EventDay0() {
    for(int num = 0 ; num <25; num++){
        switch (num%1){
            case 0:
                AddTile("ocean_tile");
                break;
        }
    }
    SetMapSquare(5);

    //std::shared_ptr<player_ctrl> player_ptr;
    player_ptr_.reset(new Paladin("Meep",(std::weak_ptr<BaseTile>) vector_of_tileptr_[0]));
    vector_of_tileptr_[0]->AddCharToTile(player_ptr_);
    map_str_to_unitptr_.insert(std::make_pair("Meep",player_ptr_));

    //Blabla default mode
    AddUnit("turtle",1);
    AddUnit("turtle",5);
    AddUnit("turtle", 20);
    InitPrintStoryAndQuestion();

    std::shared_ptr<Wumpus> wumpus_sp_ptr;
    wumpus_ptr_ = std::make_pair(true, wumpus_sp_ptr);
    wumpus_sp_ptr.reset(new Wumpus("Wumpus",(std::weak_ptr<BaseTile>) vector_of_tileptr_[7]));
    vector_of_tileptr_[7]->AddCharToTile(wumpus_sp_ptr);
    map_str_to_unitptr_.insert(std::make_pair("Wumpus",wumpus_sp_ptr));

}

void wumpus_game::GameMaster::InitPrintStoryAndQuestion() {
    std::cout << "story" << "\n";
    std::cout << "more story\n";
}

void wumpus_game::GameMaster::InitTurnMessages(std::size_t turn_no) {
    std::cout << "Today is "<<turn_no<<"\n";
}

void wumpus_game::GameMaster::AddTile(const std::string &tile_type_name) {
    std::shared_ptr<BaseTile> tile_sp;
    if (tile_type_name == "ocean_tile"){
        tile_sp.reset(new TileOcean(tile_counter_));
    }
    vector_of_tileptr_.push_back(tile_sp);
    tile_counter_++;
}


void wumpus_game::GameMaster::EventNewSpawns() {
    //Create 3 turtle, put them randomly
}

void wumpus_game::GameMaster::EventDestroyTile() {
    //
}

void wumpus_game::GameMaster::EndGameMessage() {
    std::cout << player_ptr_->game_continue.second << "\n";
}

void wumpus_game::GameMaster::AddUnit(const std::string &unit_type_name, const std::size_t location_id) {
    std::shared_ptr<BaseUnit> unit_sp;
    std::string unit_name;
    if(unit_type_name == "turtle"){
        unit_name = unit_type_name;
        unit_name.append(std::to_string(unit_counter_));
        unit_counter_++;
        unit_sp.reset(new Turtle(unit_name,(std::weak_ptr<BaseTile>) vector_of_tileptr_[location_id]));
    }


    vector_of_tileptr_[location_id]->AddCharToTile(unit_sp);
    map_str_to_unitptr_.insert(std::make_pair(unit_name,unit_sp));
}

void wumpus_game::GameMaster::EventSwapGoalTile() {

}

void wumpus_game::GameMaster::SetMapSquare(const std::size_t &num_tile_width) {
    std::size_t tile_id_num;


    for(std::shared_ptr<BaseTile>& tile: vector_of_tileptr_){
        //adding tile id, with certain reference name dir attached to tile.
        //
        auto AttachRoom = [&tile, this](int roomID,std::string dir){
            tile->map_of_neighbour_tile_.insert(
                    std::make_pair(dir,(std::weak_ptr<BaseTile>)vector_of_tileptr_[roomID]));
        };

        tile_id_num = tile->tile_id_;

        //Attach north room
        if((tile_id_num+1)%num_tile_width && tile->DirectionFeasable[0]){
            AttachRoom(tile_id_num+1,"north");
        }
        //Attach room to east
        if(tile_id_num < 20 && tile->DirectionFeasable[1]){
            AttachRoom(tile_id_num+num_tile_width,"east");
        }
        //Attach to south
        if(tile_id_num%num_tile_width && tile->DirectionFeasable[2]){
            AttachRoom(tile_id_num-1,"south");
        }
        if(tile_id_num > (num_tile_width-1) && tile->DirectionFeasable[3]){
            AttachRoom(tile_id_num-num_tile_width,"west");
        }

    }

}
