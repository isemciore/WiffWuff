//
// Created by ezhang on 2015-11-13.
//

#include "PlayerCtrl.h"
#include <algorithm>
#include <iostream>

bool wumpus_game::PlayerCtrl::PickUpItem(std::vector<std::string> arguments) {
    //expect: pick -/up %item -/with %pos
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

    item* *mem_value_ptr;
    if(put_in_loc == "right"){
        if(right_hand_ == nullptr)
        mem_value_ptr = &right_hand_;
    } else if(put_in_loc =="left"){
        mem_value_ptr = &left_hand_;
    } else{
        std::cout << "can only pick up  item with you right or left hand and not with "<<put_in_loc<<"\n";
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
    std::cout << "Picking up item "<<(*mem_value_ptr)->get_name() << " with "<<
              put_in_loc <<" hand \n";
    return true;
}

bool wumpus_game::PlayerCtrl::DropItem(std::vector<std::string> arguments) {
    //Drop %Item from %RightHand
    int dummy_text=0;
    if (arguments.size()<3) {
        return false;
    }
    if (arguments[2].compare("from")){
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
    item* item_ptr = (*(mem_value_itr->second))->get_item(drop_item_name);
    if (item_ptr == nullptr){
        std::cout << "cannot find item";
        return false;
    }
    *(mem_value_itr->second) = nullptr;
    location_tile_pointer_.lock()->AddItem(item_ptr);
    return false;
}

wumpus_game::PlayerCtrl::PlayerCtrl(std::string name, std::weak_ptr<BaseTile> bstile)
    : BaseUnit(name, bstile){
    map_of_item_slot_.insert(std::make_pair("right",&right_hand_));
    map_of_item_slot_.insert(std::make_pair("back",&back_));
    map_of_item_slot_.insert(std::make_pair("left",&left_hand_));
    map_of_item_slot_.insert(std::make_pair("head",&head_slot_));

}

bool wumpus_game::PlayerCtrl::MoveItem(std::vector<std::string> arguments) {
    //move item from backpack   to      right   hand
    //move item from right      hand    to      backpack
    //move item from right      hand    to      left     hand
    if (arguments.size() < 7){
        return false;
    }
    std::string item_name = arguments[1];
    std::string from_loc  = arguments[3];
    std::string to_loc    = arguments[6];
    if (arguments[6].compare("hand")){
        std::string to_loc    = arguments[5];
    }

    map_of_item_slot_type::iterator from_itr = map_of_item_slot_.find(from_loc);
    map_of_item_slot_type::iterator to_itr   = map_of_item_slot_.find(to_loc);
    if (from_itr == map_of_item_slot_.end() ||  to_itr == map_of_item_slot_.end()){
        std::cout << "bad input, expect move $item from $position to $position \n";
        return false;
    }

    if ( *(to_itr->second) != nullptr){
        std::cout << "desitination is not empty \n";
        return false;
    }
    item* item_ptr = (*(from_itr->second))->get_item(item_name);
    if (item_ptr == nullptr){
        std::cout << "cannot find item\n";
        return false;
    }
    *(from_itr->second) = nullptr;
    *(to_itr->second)  = item_ptr;
    std::cout << "you move item "<< item_ptr->get_name() <<" \n";
    return true;
}

bool wumpus_game::PlayerCtrl::DisplayWield(std::vector<std::string> arguments) {
    for(auto & item_itr  : map_of_item_slot_){
        container* container_ptr = dynamic_cast<container*>(*(item_itr.second));
        if (nullptr ==container_ptr){
            if (*(item_itr.second) != nullptr) {
                std::cout << (*(item_itr.second))->get_name() << ", ";
            }
        }else{
            if (container_ptr != nullptr) {
                std::cout << container_ptr->get_name() << "containers the item";
                container_ptr->Display_contents();
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
