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
#include "enviroment/tile_escape_win.h"
#include "character/sorcerer.h"

wumpus_game::GameMaster::GameMaster() {
    turn_number_ = 0;
}

void wumpus_game::GameMaster::GameStart() {

    unit_iterator_type unit_it_begin;
    unit_iterator_type unit_it_end;
    bool add_googles_once = false;
    bool run_once_wumpus = false;
    for (turn_number_; true; turn_number_++) { //Iterate each turn
        std::cout << "\n\n"; //Special events
        if (turn_number_==0){
            EventDay0();
        turn_number_++;
        }
        InitTurnMessages(turn_number_);
        if ((turn_number_+1)%3 == 0){
            EventNewSpawns();
        }
        if ((turn_number_+1)%4 == 0){
            bool player_in_tile = EventDestroyTile();//if player is in tile, break loop
            if(!player_in_tile){
                player_ptr_->game_continue = std::make_pair(false,"lava");
                break;
            }
        }

        unit_it_begin = map_str_to_unitptr_.begin();
        unit_it_end = map_str_to_unitptr_.end();
        //Let player perform action first
        player_ptr_->PerformAction();
        if (!player_ptr_->game_continue.first) {
            break;
        }
        std::cout << "Computer turn:\n";
        while((unit_it_begin != unit_it_end) && (player_ptr_->game_continue.first)){
            //if something 'dies' during computer turn it make sure to clean it up here
            while (unit_it_begin->second.expired() && unit_it_begin!=unit_it_end){
                unit_it_begin = map_str_to_unitptr_.erase(unit_it_begin);
            }
            //if it is a computer perform action
            if (unit_it_begin->second.lock() != player_ptr_) {
                unit_it_begin->second.lock()->PerformAction();
            }
            unit_it_begin++;
        }


        //check of different end game condition
        if (!player_ptr_->game_continue.second.compare("headshot") && !run_once_wumpus) {
            run_once_wumpus = true;
            std::weak_ptr<BaseTile> wumpus_tile_ptr = wumpus_ptr_.second.lock()->GetUnitLocation();
            int wumpus_id_loc = wumpus_tile_ptr.lock()->get_tile_id();
            wumpus_tile_ptr.lock()->Exit("Wumpus");
            AddItem("nightvision_googles",0.01,0.1,wumpus_id_loc);
        }


        if (!player_ptr_->game_continue.first){
            break;
        }
        if (!player_ptr_->game_continue.second.compare("googles_on") && !add_googles_once) {
            add_googles_once = true;
            EventSwapGoalTile();
        }

        if (player_ptr_->get_current_unit_hp() <=0){
            player_ptr_->game_continue = std::make_pair(false,"lowhp");
            break;
        }
    }
    EndGameMessage();
}

wumpus_game::GameMaster::~GameMaster() {

}

//Adds stuff to map initially
void wumpus_game::GameMaster::EventDay0() {
    InitPrintStoryAndQuestion();
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

    std::cout << "What kind of hero are you?, a Paladin or a Sorcerer?\n";
    std::string hero_type;
    while(true){
        std::cin >> hero_type;
        if(hero_type =="Paladin"){
            AddUnit("Paladin",0);
            break;
        } else if(hero_type == "Sorcerer"){
            AddUnit("Sorcerer",0);
            break;
        }
        std::cout << "You can only choose 'Paladin' or 'Sorcerer'" << "\n";
    }
    std::string dummy;//Force flush
    getline(std::cin,dummy);

    AddUnit("Wumpus",7);

    AddUnit("turtle",0);
    AddUnit("turtle",1);
    AddUnit("turtle",5);
    AddUnit("turtle", 20);
    AddUnit("mean_turtle",5);
    AddUnit("mean_turtle",10);

    InitialItemDrop();

}

void wumpus_game::GameMaster::InitPrintStoryAndQuestion() {
    std::string dummy;
    std::cout << "You see a dark dungeon and decides its a good ide to enter" << "\n";
    std::cout << "as soon as you step in you blackout..." << "\n";
    std::cout << "more story," << "\n";
    std::cout << "All you know, you have to find a ladder to climb out of this hole" << "\n";
    std::cout << "Input anything to continue" << "\n";
    std::cin >> dummy;
    std::cout << "\n\n\n\n\n\n";
    std::cout << "Here is the action you can do:\n";
    std::cout << "'Travel %direction' example travel north to move you character north" <<"\n";
    std::cout << "'Attack %target_name' example attack turtle" <<"\n";
    std::cout << "'Pick up %item_name with %hand' example Pick up apple with right hand" <<"\n";
    std::cout << "'Move %item_name from %position to %position', example: move apple from right hand to back\n";
    std::cout << "'Drop %item_name from %position' example: Drop apple from back \n";
    std::cout << "'Display' displays current item you are wielding\n";

    std::cout << "Input anything to continue" << "\n";
    std::cin >> dummy;
    std::cout << "'shoot %dir %dir %dir' which Paladin can do and require bow in right hand arrow in left\n";
    std::cout << "'cast %dir %dir %dir' which Sorcerer can do, and require a staff and mana\n";

}

void wumpus_game::GameMaster::InitTurnMessages(const std::size_t &turn_no) {
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
    } else if(tile_type_name == "win_tile"){
        tile_sp.reset(new Tile_escape_win(12));
        map_int_to_tileptr_.insert(std::make_pair(12,tile_sp));
        return;
    } else{
        throw std::runtime_error("tile does not exist or something picnic\n");
    }
    map_int_to_tileptr_.insert(std::make_pair(tile_counter_,tile_sp));

    //vector_of_tileptr_.push_back(tile_sp);

    tile_counter_++;
}


void wumpus_game::GameMaster::EventNewSpawns() {
    AddUnit("turtle", 5);//demonstrate new units can be introduced "mid" game
    //If tile id 5 does not exist, no turtle is added check is done in add unit.
    //Create 3 turtle, put them randomly
}

bool wumpus_game::GameMaster::EventDestroyTile() {
    if(tile_destruction_number_ >=23){
        return true;
    }
    bool playerWasInTile = RemoveTile(desutrction_order_[tile_destruction_number_]);
    tile_destruction_number_++;
    return playerWasInTile;
    //bool = player is in tile
}

void wumpus_game::GameMaster::EventSwapGoalTile() {
    map_tileptr_type::iterator remove_target = map_int_to_tileptr_.find(12);
    map_int_to_tileptr_.erase(remove_target);
    AddTile("win_tile");
    SetMapSquare(5);//repair connections
    //check east, west north south, etc for them replace with new tile and replace
    //
}

bool wumpus_game::GameMaster::RemoveTile(const int &tile_id) {
    map_tileptr_type::iterator target_tile_itr = map_int_to_tileptr_.find(tile_id);
    int target_id = player_ptr_->GetUnitLocation().lock()->get_tile_id();
    if(tile_id == target_id){
        std::cout << "The ground is shaking and you think you stand at the source" << "\n";
        return false;
    } else if (target_tile_itr != map_int_to_tileptr_.end()) {
        map_int_to_tileptr_.erase(target_tile_itr);
        std::cout << "The ground is shaking" << "\n";
    }

    return true;
}



void wumpus_game::GameMaster::EndGameMessage() {
    std::cout << "\n\n\n";
    if (player_ptr_->game_continue.second == "escape"){
        std::cout << "You begin slowly climbing the ladder,"
                " one step at a time towards the light\n";
        std::cout << "..."<<"\n";
    }else if (player_ptr_->game_continue.second == "eaten"){
        std::cout << "no more\n";
        std::cout << "Game Over\n";
    }else if (player_ptr_->game_continue.second== "lava"){
        std::cout << "room breaks up at you fell into the lava\n";
        std::cout << "Game Over\n";
    }else if (player_ptr_->game_continue.second== "lowhp"){
        std::cout << "you are hurt and cannot move and feel lifeless\n";
        std::cout << "Game Over\n";
    } else if (player_ptr_->game_continue.second == "arrowintheknee") {
        std::cout << "you accidently shoot your self \n";
    }
    else{
        std::cout << "uncoded end condition: " << player_ptr_->game_continue.second << "\n";
    }
}

void wumpus_game::GameMaster::AddUnit(const std::string &unit_type_name, const int location_id) {
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
    } else if(unit_type_name == "Paladin"){
        unit_sp.reset(new Paladin("Meep", tile_target_weak));
        player_ptr_ = std::dynamic_pointer_cast<PlayerCtrl> (unit_sp);
    } else if (unit_type_name == "Sorcerer"){
        unit_sp.reset(new Sorcerer("Meep", tile_target_weak));
        player_ptr_ = std::dynamic_pointer_cast<PlayerCtrl> (unit_sp);
    } else if (unit_type_name == "Wumpus"){
        unit_name = "Wumpus";
        unit_sp.reset(new Wumpus("Wumpus",tile_target_weak));
        std::weak_ptr<Wumpus> temp = std::dynamic_pointer_cast<Wumpus>(unit_sp);
        wumpus_ptr_ = std::make_pair(true,temp);
    } else if (unit_type_name == "mean_turtle"){
        unit_name = unit_type_name;
        unit_name.append(std::to_string(unit_counter_));
        unit_counter_++;
        unit_sp.reset(new Turtle(unit_name,tile_target_weak));
        std::shared_ptr<Turtle> temp_turtle_ptr = std::dynamic_pointer_cast<Turtle>(unit_sp);
        temp_turtle_ptr->setAggresiveMode(true);
        //unit_sp.reset(new Turtle(unit_name,(std::weak_ptr<BaseTile>) vector_of_tileptr_[location_id]));
    } else {std::cout << "PICNIC NO UNIT NAMED \n";}


    tile_target_weak.lock()->AddCharToTile(unit_sp);
    //vector_of_tileptr_[location_id]->AddCharToTile(unit_sp);
    map_str_to_unitptr_.insert(std::make_pair(unit_name,unit_sp));
}

//Reconnects all connections
void wumpus_game::GameMaster::SetMapSquare(const int &num_tile_width) {
    if (num_tile_width < 1) {
        throw std::out_of_range("cannot have negative tile width \n");
    }

    //for(std::shared_ptr<BaseTile>& tile: vector_of_tileptr_){
    map_tileptr_type::iterator first_elt = map_int_to_tileptr_.begin();
    map_tileptr_type::iterator last_elt = map_int_to_tileptr_.end();
    while(first_elt!= last_elt){
        AttachNeighbour(first_elt,num_tile_width);
        first_elt++;
    }
}

void wumpus_game::GameMaster::AttachNeighbour(
        map_tileptr_type::iterator room_ptr,
        const int &num_tile_width) {
    int tile_id_num;
    std::shared_ptr<BaseTile> tile;
    tile = room_ptr->second;
    tile_id_num = tile->tile_id_;
    //adding tile id, with certain reference name dir attached to tile.
    //
    auto AttachRoom = [&tile, this](int roomID,std::string dir){
        map_tileptr_type::iterator tile_itr = map_int_to_tileptr_.find(roomID);
        if (tile_itr!=map_int_to_tileptr_.end()) {
            std::weak_ptr<BaseTile> baseTilePtr = tile_itr->second;
            tile->map_of_neighbour_tile_.erase(dir); //REFRESHES target
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

}



void wumpus_game::GameMaster::InitialItemDrop() {
    //Item* item_ptr = new Item("cardboard_box",0.1,1);/
    //vector_of_tileptr_[0]->AddItem(item_ptr);
    AddConsumable("arrow",0);
    AddConsumable("arrow",2);
    AddConsumable("arrow",14);
    AddItem("cardboard",0.1,1,0);
    AddItem("wizard_staff",0.2,0.3,10);
    AddConsumable("apple",1);
    AddContainer("backpack",10,2,1);
    AddItem("carbattery", 0.1, 100, 1);
}

void wumpus_game::GameMaster::AddItem(const std::string &itemname, const int &dest) {
    if (itemname == "cardboard") {
        AddItem("cardboard", 0.1, 1, dest);
    }//default "template" item

    else {
        AddItem(itemname, 1, 1.1, dest);
    }

}

void wumpus_game::GameMaster::AddContainer(const std::string &new_container_name, const double &new_cont_wei_cap,
                                           const double &new_cont_vol_cap, const int &dest) {
    container *container_item = new container(new_container_name, new_cont_wei_cap, new_cont_vol_cap);
    if (!new_container_name.compare("backpack")) {
        Item *air_bubble = new Item("bubble_wrap", 0.00001, 1);
        Item *bow = new Item("bow", 0.3, 0.2);
        container_item->AddItem(air_bubble);
        container_item->AddItem(bow);
    }
    AddItem(container_item,dest);
}

void wumpus_game::GameMaster::AddConsumable(const std::string &consumable_name, const int &dest) {
    if (!consumable_name.compare("apple")) {
        AddConsumable("apple", 0.06, 0.08, 20, 1, dest);
    } else if (!consumable_name.compare("arrow")) {
        AddConsumable("arrow", 0.005, 0.01, 0, 0, dest);
    } else if (!consumable_name.compare("mango")) {
        AddConsumable("mango", 0.6, 0.1, 1, 40, dest);
    } else {
        AddConsumable(consumable_name, 1, 1.1, 0, 0, dest);
    }
}

void wumpus_game::GameMaster::AddConsumable(const std::string &item_name, const double &new_item_weight,
                                            const double &new_item_volume, const double &delta_hp,
                                            const double &delta_mana,
                                            const int &dest) {
    Item* consumable = new Consumable(item_name,new_item_weight,new_item_volume,delta_hp,delta_mana);
    AddItem(consumable,dest);
}

void wumpus_game::GameMaster::AddItem(const std::string &new_item_name, const double &new_item_weight,
                                      const double &new_item_volume, const int &dest) {
    Item * item_ptr = new Item(new_item_name,new_item_weight, new_item_volume);
    if (map_int_to_tileptr_.find(dest) != map_int_to_tileptr_.end()){
        map_tileptr_type::iterator tile_ptr_itr = map_int_to_tileptr_.find(dest);
        tile_ptr_itr->second->AddItem(item_ptr);
    }else{
        delete item_ptr;
    }
    //vector_of_tileptr_[dest]->AddItem(item_ptr);
}

void wumpus_game::GameMaster::AddItem(Item *item_ptr, const int &dest) {
    if (map_int_to_tileptr_.find(dest) != map_int_to_tileptr_.end()){
        map_tileptr_type::iterator tile_ptr_itr = map_int_to_tileptr_.find(dest);
        tile_ptr_itr->second->AddItem(item_ptr);
    }else{
        delete item_ptr;
    }
    //vector_of_tileptr_[dest]->AddItem(item_ptr);
}
