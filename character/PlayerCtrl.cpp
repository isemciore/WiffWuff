//
// Created by ezhang on 2015-11-13.
//

#include "PlayerCtrl.h"
#include <algorithm>
#include <iostream>
#include "../enviroment/tile_escape_win.h"

bool wumpus_game::PlayerCtrl::PickUpItem(const std::vector<std::string>& arguments) {
    //expect: pick -/up %Item -/with %pos
    if(arguments.size()<3){
        std::cout << "not enough arguments\n";
        return false;
    }
    int shift_constant=0;
    if(!arguments[1].compare("up")){
        shift_constant++;
    }
    if(arguments.size()<(3+shift_constant)){
        std::cout << "not enough arguments\n";
        return false;
    }
    std::string item_name = arguments[1+shift_constant];
    if(!arguments[2+shift_constant].compare("with")){
        shift_constant++;
    }
    if(arguments.size()<(3+shift_constant)){
        return false;
    }
    std::string put_in_loc = arguments[2+shift_constant];

    Item * *mem_value_ptr;
    if(put_in_loc == "right"){
        if(right_hand_ == nullptr)
        mem_value_ptr = &right_hand_;
    } else if(put_in_loc =="left"){
        mem_value_ptr = &left_hand_;
    } else{
        std::cout << "can only pick up  Item with you right or left hand and not with "<<put_in_loc<<"\n";
        return false;
    }
    if(*mem_value_ptr != nullptr){
        std::cout << "Hand is occupied \n";
        return false;
    }
    *mem_value_ptr = location_tile_pointer_.lock()->GetItemPointer(item_name);
    if(*mem_value_ptr == nullptr){
        return false;
    }
    std::cout << (*mem_value_ptr)->get_name()<<"\n";
    std::cout << "Picking up Item "<<(*mem_value_ptr)->get_name() << " with "<<
              put_in_loc <<" hand \n";
    return true;
}

bool wumpus_game::PlayerCtrl::DropItem(const std::vector<std::string> &arguments) {
    //Drop %Item from %RightHand
    int dummy_text=0;
    if (arguments.size()<3) {
        return false;
    }
    if (!arguments[2].compare("from")){
        if (arguments.size()<4){
            return false;
        }
        dummy_text++;
    }
    std::string drop_from_location = arguments[2+dummy_text];
    std::string drop_item_name = arguments[1];
    map_of_item_slot_type::iterator mem_value_itr = map_of_item_slot_.find(drop_from_location);
    if (mem_value_itr==map_of_item_slot_.end()){
        std::cout <<"target location "<< drop_from_location << " does not seem to exist \n";
        return false;
    }
    Item * item_ptr = (*(mem_value_itr->second))->get_item(drop_item_name);
    if (item_ptr == nullptr){
        std::cout << "cannot find Item";
        return false;
    }
    *(mem_value_itr->second) = nullptr;
    location_tile_pointer_.lock()->AddItem(item_ptr);
    return true;
}

wumpus_game::PlayerCtrl::PlayerCtrl(const std::string name,const std::weak_ptr<BaseTile> bstile)
    : BaseUnit(name, bstile){
    map_of_item_slot_.insert(std::make_pair("right",&right_hand_));
    map_of_item_slot_.insert(std::make_pair("back",&back_));
    map_of_item_slot_.insert(std::make_pair("left",&left_hand_));
    map_of_item_slot_.insert(std::make_pair("head",&head_slot_));

}

bool wumpus_game::PlayerCtrl::MoveItem(const std::vector<std::string> &arguments) {
    //move item from backpack   to      right   hand
    //move item from right      hand    to      backpack
    //move item from right      hand    to      left     hand
    if (arguments.size() < 7){
        std::cout << "to few arguments \n";
        return false;
    }
    std::string item_name = arguments[1];
    std::string from_loc  = arguments[3];
    std::string to_loc    = "dummy";
    if(!arguments[4].compare("to")){
        to_loc = arguments[5];
    } else if(!arguments[5].compare("to")){
        to_loc = arguments[6];
    }

    map_of_item_slot_type::iterator from_itr = map_of_item_slot_.find(from_loc);
    map_of_item_slot_type::iterator to_itr   = map_of_item_slot_.find(to_loc);
    if (from_itr == map_of_item_slot_.end() ||  to_itr == map_of_item_slot_.end()){
        std::cout << "bad input, expect move $Item from $position to $position \n";
        return false;
    }

    container* from_cont_ptr = dynamic_cast<container*>(*(from_itr->second));
    container* container_ptr = dynamic_cast<container*>(*(to_itr->second));
    //pointerpointer points to some item that is not a backpack
    if ( *(to_itr->second) != nullptr && container_ptr== nullptr){
        std::cout << "desitination is not empty \n";
        return false;
    }
    Item* item_ptr = nullptr;
    if(*(from_itr->second) == nullptr){
        std::cout << " cannot find from location \n";
        return false;
    }else if(from_cont_ptr == nullptr){ //item
        item_ptr = *(from_itr->second);
        *(from_itr->second) = nullptr;
    }else{
        item_ptr = (*(from_itr->second))->get_item(item_name);
        if(item_name == (*(from_itr->second))->get_name()){
            //moving backpack
            *(from_itr->second) = nullptr;
        }
    }


    /*
    container* from_fest_cont_ptr = dynamic_cast<container*>(*(from_itr->second));
    if(from_fest_cont_ptr!= nullptr) {
        from_fest_cont_ptr->Display_contents();
    }*/
    if (item_ptr == nullptr){
        std::cout << "cannot find Item\n";
        return false;
    }

    if(item_ptr->get_name() == "nightvision_googles" && !(from_itr->first.compare("head")) ){
        std::cout <<" you try to pull off your googles, but they are stuck \n";
        return false;
    }


    //if destination is a cointer
    std::cout << "you move Item "<< item_ptr->get_name() <<" \n";
    if(container_ptr!= nullptr){
        container_ptr->AddItem(item_ptr);
        std::cout << "into a container ";
    }else {
        *(to_itr->second) = item_ptr;
    }
    std::cout << "in/on "<< to_itr->first << "\n";

    if(!item_ptr->get_name().compare("nightvision_googles") && !to_itr->first.compare("head")){
        std::cout << " and you now you can see your surrounding clearly\n";
        game_continue = std::make_pair(true,"googles_on");
    }

    return true;
}

bool wumpus_game::PlayerCtrl::DisplayWield(const std::vector<std::string> &arguments) {
    /*
    if(right_hand_ != nullptr){
        container* container_ptr = dynamic_cast<container*>(right_hand_);
        std::cout << "In your right hand you have a ";
        if(container_ptr!= nullptr){
            std::cout << container_ptr->get_name() << " which contains the item";
            container_ptr->Display_contents();
        }else{
            std::cout << right_hand_->get_name();
        }
        std::cout << "\n";
    }
    if(left_hand_ != nullptr){
        container* container_ptr = dynamic_cast<container*>(left_hand_);
        std::cout << "In your left hand you have a ";
        if(container_ptr!= nullptr){
            std::cout << container_ptr->get_name() << " which contains the item";
            container_ptr->Display_contents();
        }else{
            std::cout << left_hand_->get_name();
        }
        std::cout << "\n";
    }
    if(head_slot_ != nullptr){
        container* container_ptr = dynamic_cast<container*>(head_slot_);
        std::cout << "On your head you have a ";
        if(container_ptr!= nullptr){
            std::cout << head_slot_->get_name() << " which contains the item";
            container_ptr->Display_contents();
        }else{
            std::cout << head_slot_->get_name();
        }
        std::cout << "\n";
    }

    if(back_ != nullptr){
        container* container_ptr = dynamic_cast<container*>(back_);
        std::cout << "On your back you have a ";
        if(container_ptr!= nullptr){
            std::cout << container_ptr->get_name() << " which contains the item";
            container_ptr->Display_contents();
        }else{
            std::cout << back_->get_name();
        }
        std::cout << "\n";
    }
     */

    for(auto & item_itr  : map_of_item_slot_){
        container* container_ptr = dynamic_cast<container*>(*(item_itr.second));
        if (nullptr ==container_ptr){ //regular item in location
            if (*(item_itr.second) != nullptr) {
                std::cout << "In your "<< item_itr.first << " you have ";
                std::cout << (*(item_itr.second))->get_name() << ", ";
            }
        }else{//a backpack at location
            if (container_ptr != nullptr) {
                std::cout << "In your "<<item_itr.first<< " you have a ";
                std::cout << container_ptr->get_name() << " which contains the item(s) ";
                container_ptr->Display_contents();
                std::cout << " ";
            }
        }
    }
    std::cout << "\n";
    return false;
}

wumpus_game::PlayerCtrl::~PlayerCtrl() {
    for(auto & item_pair : map_of_item_slot_){
        if ( *item_pair.second != nullptr){
            delete (*item_pair.second);
            *item_pair.second = nullptr;
        }
    }
}

bool wumpus_game::PlayerCtrl::ConsumeItem(const std::vector<std::string> &arguments) {
    if(arguments.size()<2){
        return false;
    }
    std::string item_name_to_be_consumed = arguments[1];
    if(left_hand_!= nullptr && left_hand_->get_name() == item_name_to_be_consumed){
        Consumable* item_to_be_constumed = dynamic_cast<Consumable*> (left_hand_);
        if(item_to_be_constumed != nullptr){
            item_to_be_constumed->Consume(this);/*
            if(item_to_be_constumed->get_delta_hp() != 0){
                current_health += item_to_be_constumed->get_delta_hp();
                std::cout << "you gain health\n";
            }
            if(item_to_be_constumed->get_delta_mana() != 0){
                current_mana += item_to_be_constumed->get_delta_mana();
                std::cout << "you gain mana\n";
            }*/
            std::cout << "you used up "<< item_name_to_be_consumed << "\n";
            delete left_hand_;
            left_hand_ = nullptr;
            return true;
        }
        else{
            std::cout << "cannot eat that\n";
        }
    }else{
        std::cout << item_name_to_be_consumed << " is not in your left hand\n";
    }
    if(current_health <= 0){
        game_continue = std::make_pair(false,"poison");
        //Continue game false
    }

    return false;
}

bool wumpus_game::PlayerCtrl::ClimbLadder(const std::vector<std::string> &arguments) {

    std::shared_ptr<Tile_escape_win> sp_t_win =
            std::dynamic_pointer_cast<Tile_escape_win> (location_tile_pointer_.lock());
    if(sp_t_win!= nullptr){
        game_continue = std::make_pair(false,"escape");
        return true;
    }
    std::cout << "you scratch the walls.. nothing happens \n";
    return false;
}
