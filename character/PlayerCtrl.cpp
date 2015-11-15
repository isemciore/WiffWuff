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
        std::cout << "not enough arguments\n";
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
    //Drop right
    //Drop left
    //Drop head -- noo do not do that
    //Drop item from backpack
    return false;
}
