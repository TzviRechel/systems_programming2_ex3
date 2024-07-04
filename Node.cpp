// tzvirechel@gmail.com
#include <iostream>
#include "Player.hpp"
#include "Node.hpp"


Node::Node(){
    _hasSettlement = false;
    _hasCity = false;
    _playerID = 0;
}

bool Node::hasCity(){
    return _hasCity;
}

bool Node::hasSettlement(){
    return _hasSettlement;
}

int Node::getPlayer(){
    return _playerID;
}

void Node::setSettlement(int playerID){
    if(_hasSettlement){return;}
    _hasSettlement = true;
    _playerID = playerID;
}

void Node::setCity(){
    _hasSettlement = false;
    _hasCity = true;   
}
    