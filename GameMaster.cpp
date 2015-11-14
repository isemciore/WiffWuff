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
    //std::shared_ptr<player_ctrl> player_ptr;
    player_ptr_.reset(new Paladin("Meep",(std::weak_ptr<BaseTile>) vector_of_tileptr_[0]));
    vector_of_tileptr_[0]->AddCharToTile(player_ptr_);
    map_str_to_unitptr_.insert(std::make_pair("Meep",player_ptr_));

    //Blabla default mode
    AddUnit("turtle",1);
    AddUnit("turtle",5);
    AddUnit("turtle", 20);
    InitPrintStoryAndQuestion();


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
