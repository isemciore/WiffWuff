#include "character/baseunit.h"
#include "gamemaster.h"

using namespace wumpus_game;


int main() {
    //std::cout << "Start a new game or load game?" << std::endl;
    //load game, send data file to savefile type then gameEvent(savefile);

    GameMaster gameEvent;
    gameEvent.GameStart();

    //std::shared_ptr<int> sharedPointer_int;
    //sharedPointer_int.reset(new int);


    return 0;
}
