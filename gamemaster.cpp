//
// Created by erik on 2015-11-10.
//

#include <iostream>
#include "gamemaster.h"
#include "enviroment/tile_ocean.h"
#include "character/paladin.h"
#include "character/turtle.h"
#include "enviroment/tile_mountain_ridge.h"
#include "enviroment/tile_dark_room.h"
#include "stuff/Consumable.h"

wumpus_game::GameMaster::GameMaster() {
    turn_number_ = 0;
}

void wumpus_game::GameMaster::GameStart() {

    unit_iterator_type unit_it_begin;
    unit_iterator_type unit_it_end;

    bool run_once_wumpus = false;
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
            EventDestroyTile();//if player is in tile, break loop
        }
        unit_it_begin = map_str_to_unitptr_.begin();
        unit_it_end = map_str_to_unitptr_.end();

        while ((unit_it_begin != unit_it_end) && unit_it_begin->second.expired()){
            unit_it_begin = map_str_to_unitptr_.erase(unit_it_begin);
        }
        while((unit_it_begin != unit_it_end) && (player_ptr_->game_continue.first)){
            unit_it_begin->second.lock()->PerformAction();
            unit_it_begin++;
            while (unit_it_begin->second.expired() && unit_it_begin!=unit_it_end){
                unit_it_begin = map_str_to_unitptr_.erase(unit_it_begin);
            }
        }

        if (!player_ptr_->game_continue.second.compare("headshot") && run_once_wumpus == false){
            run_once_wumpus = true;
            //WUMPUS NULL SHARED MEMroy some reason



            //lock wumpus pointer, then check where it "was" shoot is special event and is erased from here
            //int wumpus_id_loc = wumpus_ptr_.second.lock()->GetUnitLocation().lock()->tile_id_;
            std::weak_ptr<BaseTile> wumpus_tile_ptr = wumpus_ptr_.second.lock()->GetUnitLocation();
            std::size_t wumpus_id_loc = wumpus_tile_ptr.lock()->get_tile_id();
            wumpus_tile_ptr.lock()->exit("Wumpus");
            //wumpus_ptr_.second.lock()->GetUnitLocation().lock()->map_of_char_in_tile_.erase("wumpus");
            AddItem("nightvision_googles",0.01,0.1,wumpus_id_loc);
            //Add Item to the ground
        }


        if (!player_ptr_->game_continue.first){
            std::cout << player_ptr_->game_continue.first << " with the next line rror msg " << player_ptr_->game_continue.second << "\n";
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
        if(num == 0){
            AddTile("ocean_tile");
        } else if(num == 12){
            AddTile("dark_tile");
        } else{
            if(num%5 == 0 || num%5==2 || num%5==4){
                AddTile("mountain_ridge");
            }
            else{
                AddTile("ocean_tile");
            }
        }
    }
    SetMapSquare(5);

    //std::shared_ptr<PlayerCtrl> player_ptr;
    //player_ptr_.reset(new Paladin("Meep",(std::weak_ptr<BaseTile>) vector_of_tileptr_[0]));
    //vector_of_tileptr_[0]->AddCharToTile(player_ptr_);
    //map_str_to_unitptr_.insert(std::make_pair("Meep",player_ptr_));
    AddUnit("Meep",0);
    AddUnit("Wumpus",7);

    //Blabla default mode
    AddUnit("turtle",1);
    AddUnit("turtle",5);
    AddUnit("turtle", 20);
    InitPrintStoryAndQuestion();

    //std::shared_ptr<Wumpus> wumpus_sp_ptr;
    //wumpus_sp_ptr.reset(new Wumpus("Wumpus",(std::weak_ptr<BaseTile>) vector_of_tileptr_[7]));
    //wumpus_ptr_ = std::make_pair(true, wumpus_sp_ptr);
    //vector_of_tileptr_[7]->AddCharToTile(wumpus_sp_ptr);
    //map_str_to_unitptr_.insert(std::make_pair("Wumpus",wumpus_sp_ptr));


    InitialItemDrop();

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
    } else if(tile_type_name == "mountain_ridge"){
        tile_sp.reset(new TileMountainRidge(tile_counter_));
    } else if(tile_type_name == "dark_tile"){
        tile_sp.reset(new TileDarkRoom(tile_counter_));
    }
    else{
        throw std::runtime_error("tile does not exist or something picnic\n");
    }
    map_int_to_tileptr_.insert(std::make_pair(tile_counter_,tile_sp));

    //vector_of_tileptr_.push_back(tile_sp);

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
    //first check if location exist
    map_tileptr_type::iterator tile_itr = map_int_to_tileptr_.find(location_id);
    if (tile_itr == map_int_to_tileptr_.end()){
        return;
    }
    std::weak_ptr<BaseTile> tile_target_weak = tile_itr->second;

    //then add unit to that location
    if(unit_type_name == "turtle"){
        unit_name = unit_type_name;
        unit_name.append(std::to_string(unit_counter_));
        unit_counter_++;
        unit_sp.reset(new Turtle(unit_name,tile_target_weak));
        //unit_sp.reset(new Turtle(unit_name,(std::weak_ptr<BaseTile>) vector_of_tileptr_[location_id]));
    } else if (unit_type_name == "Meep"){
        unit_name = "Meep";
        unit_sp.reset(new Paladin("Meep", tile_target_weak));
        player_ptr_ = std::dynamic_pointer_cast<PlayerCtrl> (unit_sp);
    } else if (unit_type_name == "Wumpus"){
        unit_name = "Wumpus";
        unit_sp.reset(new Wumpus("Wumpus",tile_target_weak));
        std::weak_ptr<Wumpus> temp = std::dynamic_pointer_cast<Wumpus>(unit_sp);
        wumpus_ptr_ = std::make_pair(true,temp);
    }

    else{std::cout << "PICNIC NO UNIT NAMED \n";}


    tile_target_weak.lock()->AddCharToTile(unit_sp);
    //vector_of_tileptr_[location_id]->AddCharToTile(unit_sp);
    map_str_to_unitptr_.insert(std::make_pair(unit_name,unit_sp));
}

void wumpus_game::GameMaster::EventSwapGoalTile() {

}

void wumpus_game::GameMaster::SetMapSquare(const std::size_t &num_tile_width) {
    std::size_t tile_id_num;
    std::shared_ptr<BaseTile> tile;

    //for(std::shared_ptr<BaseTile>& tile: vector_of_tileptr_){
    map_tileptr_type::iterator first_elt = map_int_to_tileptr_.begin();
    map_tileptr_type::iterator last_elt = map_int_to_tileptr_.end();
    while(first_elt!= last_elt){
        tile = first_elt->second;
        tile_id_num = tile->tile_id_;

        //adding tile id, with certain reference name dir attached to tile.
        //
        auto AttachRoom = [&tile, this](int roomID,std::string dir){
            map_tileptr_type::iterator tile_itr = map_int_to_tileptr_.find((std::size_t) roomID);
            if (tile_itr!=map_int_to_tileptr_.end()) {
                std::weak_ptr<BaseTile> baseTilePtr = tile_itr->second;
                tile->map_of_neighbour_tile_.insert(std::make_pair(dir,baseTilePtr));

            }
        };
            /*
            tile->map_of_neighbour_tile_.insert(
                    std::make_pair(dir,(std::weak_ptr<BaseTile>)vector_of_tileptr_[roomID]));
            */
        //Attach north room
        if((tile_id_num+1)%num_tile_width && tile->feaseable_direction[0]){
            AttachRoom(tile_id_num+1,"north");
            //BaseTile::neighbour_map_type::iterator tilePair =  tile->map_of_neighbour_tile_.find("north");
            //std::cout << tilePair->second.lock()->get_tile_id()<<"\n";
        }
        //Attach room to east
        if(tile_id_num < 20 && tile->feaseable_direction[1]){
            AttachRoom(tile_id_num+num_tile_width,"east");
        }
        //Attach to south
        if(tile_id_num%num_tile_width && tile->feaseable_direction[2]){
            AttachRoom(tile_id_num-1,"south");
        }
        if(tile_id_num > (num_tile_width-1) && tile->feaseable_direction[3]){
            AttachRoom(tile_id_num-num_tile_width,"west");
        }


        first_elt++;
    }

}

void wumpus_game::GameMaster::InitialItemDrop() {
    //Item* item_ptr = new Item("cardboard_box",0.1,1);
    //vector_of_tileptr_[0]->AddItem(item_ptr);
    AddItem("cardboard",0.1,1,0);
    AddConsumable("apple",1);
}


void wumpus_game::GameMaster::AddConsumable(std::string item_name, int dest){
    if(!item_name.compare("apple")){
        AddConsumable("apple",0.1,0.08,20,1,dest);
    }
}

void wumpus_game::GameMaster::AddConsumable(std::string item_name, double new_item_weight,double new_item_volume,double delta_hp, double delta_mana, int dest){
    Item* consumable = new Consumable(item_name,new_item_weight,new_item_volume,delta_hp,delta_mana);
    AddItem(consumable,dest);
}

void wumpus_game::GameMaster::AddItem(std::string new_item_name, double new_item_weight, double new_item_volume, int dest) {
    Item * item_ptr = new Item(new_item_name,new_item_weight, new_item_volume);
    if (map_int_to_tileptr_.find(dest) != map_int_to_tileptr_.end()){
        map_tileptr_type::iterator tile_ptr_itr = map_int_to_tileptr_.find(dest);
        tile_ptr_itr->second->AddItem(item_ptr);
    }else{
        delete item_ptr;
    }
    //vector_of_tileptr_[dest]->AddItem(item_ptr);
}

void wumpus_game::GameMaster::AddItem(Item * item_ptr, int dest) {
    if (map_int_to_tileptr_.find(dest) != map_int_to_tileptr_.end()){
        map_tileptr_type::iterator tile_ptr_itr = map_int_to_tileptr_.find(dest);
        tile_ptr_itr->second->AddItem(item_ptr);
    }else{
        delete item_ptr;
    }
    //vector_of_tileptr_[dest]->AddItem(item_ptr);
}