//
// Created by ezhang on 2015-11-27.
//

#include <iostream>
#include <sstream>
#include <iterator>
#include "sorcerer.h"

wumpus_game::Sorcerer::Sorcerer(const std::string name,const std::weak_ptr<BaseTile> init_pos)
    : PlayerCtrl(name,init_pos){
    map_of_member_action_.insert(std::make_pair("Travel", &BaseUnit::Travel));
    map_of_member_action_.insert(std::make_pair("Attack", &BaseUnit::Attack));
    map_of_member_action_.insert(std::make_pair("Pick"  , &PlayerCtrl::PickUpItem));
    map_of_member_action_.insert(std::make_pair("Display",&PlayerCtrl::DisplayWield));
    map_of_member_action_.insert(std::make_pair("Move",   &PlayerCtrl::MoveItem));
    map_of_member_action_.insert(std::make_pair("Drop",   &PlayerCtrl::DropItem));
    map_of_member_action_.insert(std::make_pair("Cast",  &Sorcerer::Cast_spell));
    map_of_member_action_.insert(std::make_pair("Climb",  &PlayerCtrl::ClimbLadder));


    map_of_member_action_.insert(std::make_pair("travel", &BaseUnit::Travel));
    map_of_member_action_.insert(std::make_pair("attack", &BaseUnit::Attack));
    map_of_member_action_.insert(std::make_pair("pick"  , &PlayerCtrl::PickUpItem));
    map_of_member_action_.insert(std::make_pair("display",&PlayerCtrl::DisplayWield));
    map_of_member_action_.insert(std::make_pair("move",   &PlayerCtrl::MoveItem));
    map_of_member_action_.insert(std::make_pair("drop",   &PlayerCtrl::DropItem));
    map_of_member_action_.insert(std::make_pair("cast",  &Sorcerer::Cast_spell));
    map_of_member_action_.insert(std::make_pair("climb",  &PlayerCtrl::ClimbLadder));
}

void wumpus_game::Sorcerer::PerformAction() {
    std::string user_input_args;
    bool event_success;//

    location_tile_pointer_.lock()->PrintPlayerOptionAndInformation();

    while(true){
        event_success = false;
        getline(std::cin,user_input_args);
        std::stringstream ss(user_input_args);
        std::istream_iterator<std::string> begin(ss);
        std::istream_iterator<std::string> end;
        std::vector<std::string> vectorize_user_input(begin,end);
        vectorize_user_input.push_back("filler");
        vectorize_user_input.push_back("filler");

        map_of_member_action_type::iterator member_function_pair_iterator = map_of_member_action_.find(vectorize_user_input[0]);
        if(member_function_pair_iterator == map_of_member_action_.end()){
            std::cout << "unknown input\n";
        }else{
            member_function_ptr_type member_ptr = member_function_pair_iterator->second;

            event_success = ((*this).*member_ptr)(vectorize_user_input);
        }

        if(event_success && (vectorize_user_input[0]=="Travel" || vectorize_user_input[0] == "travel")){
            if(location_tile_pointer_.lock()->is_wumpus_here()){
                std::cout << "oh noo you walked into Wumpus\n";
                game_continue = std::make_pair(false,"eaten");
            }
            location_tile_pointer_.lock()->PrintTileDependentInformation();
            break;
        }
        if(event_success && vectorize_user_input[0]=="Climb"){
            game_continue = std::make_pair(false,"win");
            break;
        }

        if(game_continue.first==false){
            break;
        }
    }
}

bool wumpus_game::Sorcerer::Cast_spell(const std::vector<std::string> &input_cmds) {
    if (current_mana < 40){
        std::cout << "you do not have enough mana to cast a firball \n";
        return false;
    } else if(right_hand_== nullptr|| right_hand_->get_name().compare("wizard_staff")){
        std::cout << "missing a wizard_staff in your right ahnd \n";
        return false;
    }

    current_mana-=40;
    std::cout << "you have "<<current_mana << "left \n";
    std::weak_ptr<BaseTile> current_inspected_tile = location_tile_pointer_.lock();
    BaseTile::neighbour_map_type neighbour_map;
    BaseTile::neighbour_map_type::iterator neib_itr;
    for(int i = 1; i < 4;i++){
        neighbour_map = current_inspected_tile.lock()->get_neigbour_map();
        neib_itr = neighbour_map.find(input_cmds[i]);
        if (neib_itr  != neighbour_map.end()){
            current_inspected_tile = neib_itr->second;
            if (current_inspected_tile.lock()->is_wumpus_here()){
                std::cout << "You hear an explosion and smell burned meat"
                                     ", and are confident you got a big game\n";
                game_continue = std::make_pair(true,"headshot");
                return true;
            } else if (current_inspected_tile.lock() == location_tile_pointer_.lock()){
                game_continue = std::make_pair(false,"arrowintheknee");
                return true;
            }
        }
    }

    return false;
}
