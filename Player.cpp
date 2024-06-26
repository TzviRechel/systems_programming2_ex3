#include <vector>
#include <iostream>
#include <string>
#include "Resource.hpp"
#include "Player.hpp"
#include "DevCard.hpp"



Player::Player(std::string name, int id): _name(name), _id(id){}

int Player::getId(){
    return this->_id;
}

std::string Player::getName(){
    return _name;
}

int Player::getVictoryPoints(){
    return this->_victoryPoints;
}

void Player::addVictoryPoint(){
    this->_victoryPoints++;
}


int Player::getResource(Resource res){

    return resources[res];
}

void Player::addResource(Resource res){
    resources[res]++;
}
void Player::removeResource(Resource res, int num){
    if(res < 0 || res > 4){
        std::cerr << "enter number between 0 to 4" << std::endl; return;}
    if(resources[res]-num < 0){
        std::cerr << "you are not have enough cards from this type" << std::endl; return;
    }    
    resources[res]-=num;
}

int Player::getDevCard(DevCard card){
    return developmentCard[card];
}

void Player::addDevCard(DevCard card){
    developmentCard[card]++;

    }
    void Player::removeDevCard(DevCard card, int num){
        developmentCard[card]-=num;
    }

void Player::printResource(){
        std::cout << _name << ": " ;
        std::cout << "wood: " << resources[0] << ", ";
        std::cout << "brick: " << resources[1] << ", ";
        std::cout << "sheep: " << resources[2] << ", ";
        std::cout << "wheat: " << resources[3] << ", ";
        std::cout << "ore: " << resources[4] << std::endl;
    
}

void Player::addKnight(){
    openKnights++;
}

int Player::getKnight(){
    return openKnights;
}

void Player::subtractPoints(){
    _victoryPoints--;
}

int Player::numOfResourcesCards(){
    int sum = 0;
    for (size_t i = 0; i < 5; i++)
    {
        sum += resources[i];
    }

    return sum;   
}




