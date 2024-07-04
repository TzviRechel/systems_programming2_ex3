// tzvirechel@gmail.com
#include <iostream>
#include "Player.hpp"
#include "Edge.hpp"


Edge::Edge(){
    _hasRoad  = false;
    _playerID = -1;
}

bool Edge::hasRoad(){
    return _hasRoad;
}

int Edge::getPlayer(){
    return _playerID;
}

void Edge::setRoad(int playerID){
    if(_hasRoad){return;}
    _hasRoad  = true;
    _playerID = playerID;
}


