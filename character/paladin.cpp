//
// Created by ezhang on 2015-11-14.
//

#include "paladin.h"
#include <iostream>
#include <sstream>
#include <iterator>

wumpus_game::Paladin::Paladin(const std::string name,const std::weak_ptr<BaseTile> init_pos)
    : PlayerCtrl(name, init_pos){
    map_of_member_action_.insert(std::make_pair("Travel", &BaseUnit::Travel));
    map_of_member_action_.insert(std::make_pair("Attack", &BaseUnit::Attack));
    map_of_member_action_.insert(std::make_pair("Pick"  , &PlayerCtrl::PickUpItem));
    map_of_member_action_.insert(std::make_pair("Display",&PlayerCtrl::DisplayWield));
    map_of_member_action_.insert(std::make_pair("Move",   &PlayerCtrl::MoveItem));
    map_of_member_action_.insert(std::make_pair("Drop",   &PlayerCtrl::DropItem));
    map_of_member_action_.insert(std::make_pair("Shoot",  &Paladin::Shoot));
    map_of_member_action_.insert(std::make_pair("Climb",  &PlayerCtrl::ClimbLadder));
    map_of_member_action_.insert(std::make_pair("Consume", &PlayerCtrl::ConsumeItem));


    map_of_member_action_.insert(std::make_pair("travel", &BaseUnit::Travel));
    map_of_member_action_.insert(std::make_pair("attack", &BaseUnit::Attack));
    map_of_member_action_.insert(std::make_pair("pick"  , &PlayerCtrl::PickUpItem));
    map_of_member_action_.insert(std::make_pair("display",&PlayerCtrl::DisplayWield));
    map_of_member_action_.insert(std::make_pair("move",   &PlayerCtrl::MoveItem));
    map_of_member_action_.insert(std::make_pair("drop",   &PlayerCtrl::DropItem));
    map_of_member_action_.insert(std::make_pair("shoot",  &Paladin::Shoot));
    map_of_member_action_.insert(std::make_pair("climb",  &PlayerCtrl::ClimbLadder));
    map_of_member_action_.insert(std::make_pair("consume", &PlayerCtrl::ConsumeItem));


}

void wumpus_game::Paladin::PerformAction() {
    std::string user_input_args;

    bool event_success;//
    location_tile_pointer_.lock()->PrintPlayerOptionAndInformation();
    while(true){
        event_success = false;
        //SPLITTING USER INPUT TO VECTOR OF STRINGS
        getline(std::cin,
                user_input_args);//http://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
        std::stringstream ss(user_input_args);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vectorize_user_input(begin,end);
        vectorize_user_input.push_back("filler");
        vectorize_user_input.push_back("filler");
        ///

        map_of_member_action_type::iterator member_function_pair_iterator = map_of_member_action_.find(vectorize_user_input[0]);
        if(member_function_pair_iterator == map_of_member_action_.end()){
            std::cout << "unknown input\n";
        }else{
            member_function_ptr_type member_ptr = member_function_pair_iterator->second;

            event_success = ((*this).*member_ptr)(vectorize_user_input);
        }

        if(event_success && (vectorize_user_input[0]=="Travel" || vectorize_user_input[0] == "travel")){
            location_tile_pointer_.lock()->PrintTileDependentInformation();
            if(location_tile_pointer_.lock()->is_wumpus_here()){
                std::cout << "oh noo you walked into Wumpus\n";
                game_continue = std::make_pair(false,"eaten");
            }
            break;
        }

        if (event_success && (vectorize_user_input[0]=="Attack" || vectorize_user_input[0] == "attack")){
            break;
        }


        if(event_success && vectorize_user_input[0]=="Climb"){
            game_continue = std::make_pair(false,"win");
            break;
        }

        if (!game_continue.first) {
            break;
        }
    }
}

bool wumpus_game::Paladin::Shoot(const std::vector<std::string> &input_cmds) {
    //Check if atleast 4 "words"
    if (input_cmds.size() < 4){
        std::cout << "no enough input\n";
    }
    //check if character has a bow
    if(right_hand_ == nullptr || right_hand_->get_name().compare("bow")){
        std::cout << "cannot shoot, no bow in your right hand" << "\n";
        return false;
    }
    //arrow is consumable, mayby strength test under consume?
    std::vector<std::string> dummy;//simulate "consume arrow" input
    dummy.push_back("dummy");
    dummy.push_back("arrow");
    std::weak_ptr<BaseTile> current_inspected_tile = location_tile_pointer_.lock();
    if(!location_tile_pointer_.lock()->shoot_able_from_room()){
        std::cout << "you cannot draw your bow in this room";
        return false;
    }
    //or add user does not have enough agility to use?
    bool haveArrow = this->ConsumeItem(dummy);
    if(!haveArrow){
        std::cout << "there is no arrow in your left hand cannot shoot";
        return false;
    }

    BaseTile::neighbour_map_type neighbour_map;
    BaseTile::neighbour_map_type::iterator neib_itr;
    //For each word as position 2,3,4 check location, if direction is not possible, the arrow floats
    for(int i = 1; i < 4;i++){
        neighbour_map = current_inspected_tile.lock()->get_neigbour_map();
        neib_itr = neighbour_map.find(input_cmds[i]);
        if (neib_itr  != neighbour_map.end()){
            current_inspected_tile = neib_itr->second;
            if (current_inspected_tile.lock()->is_wumpus_here()){
                std::cout << "You here something wimpering in the distance, and are confident you got a big game\n";
                game_continue = std::make_pair(true,"headshot");
                return true;
            } else if (current_inspected_tile.lock() == location_tile_pointer_.lock()){
                std::cout << "you see a black dot coming at you\n";
                game_continue = std::make_pair(false,"arrowintheknee");
                return true;
            }
        }
    }
    return false;


}
