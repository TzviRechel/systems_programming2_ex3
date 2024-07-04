// tzvirechel@gmail.com
#include <iostream>
#include "Node.hpp"
#include "Edge.hpp"
#include "Resource.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "DevCard.hpp"

bool isFirstTurn = true;
bool devCard = false;


Game::Game(Player p1, Player p2, Player p3): _p1(p1), _p2(p2), _p3(p3), _playerTurn(&_p1), knightsOwner(nullptr){
    
}
Board &Game::getBoard(){
    return this->_board;
}

Player& Game::getPlayer(int id){
    switch(id){
    case 1: return _p1;
    case 2: return _p2; 
    case 3: return _p3; 
  }
  return _p1;
}


Player &Game::getCurrentPlayer(){
    return *_playerTurn;
}


void Game::giveResources(){
    for (size_t i = 0; i < 5; i++)
            {
                for (size_t j = 0; j < 5; j++)
                {
                        Tile& t = _board.getTiles()[i][j];
                        for (size_t p = 0; p < 6; p++)
                        {
                            Node& n = t.getNode(p);
                            if(n.hasSettlement()){
                                switch (n.getPlayer())
                                {
                                case 1:
                                    _p1.addResource(t.getResource());
                                    break;
                                case 2:
                                    _p2.addResource(t.getResource());
                                    break;   
                                case 3:
                                    _p3.addResource(t.getResource());
                                    break;    
                                
                                default:
                                    break;
                                }   

                            }
                        }
                }
                
            }
            isFirstTurn = false; 
}


std::string getResourceName(Resource resource) {
    switch (resource) {
        case Wood:
            return "Wood";
        case Brick:
            return "Brick";
        case Sheep:
            return "Sheep";
        case Wheat:
            return "Wheat";
        case Ore:
            return "Ore";
        case Desert:
            return "Desert";
        case None:
            return "None";
        default:
            return "Unknown";
    }
}




    
//void initializeGame(); 
        // void Game::playTurn(){
            
        // } 
    
        void Game::nextPlayer(){
            int cur = (*_playerTurn).getId();
            switch (cur)
            {
            case 1:
                _playerTurn = &_p2;
                break;
            case 2:
                _playerTurn = &_p3;
                break;
            case 3:
                _playerTurn = &_p1;
                break;    
            default:
                break;
            }
            std::cout << "player " << _playerTurn->getId() << " turn" << "(" << _playerTurn->getName() << ")" << std::endl;
        }
    
        bool Game::placeSettlement(size_t row, size_t col, size_t side){
            if(!isFirstTurn || devCard){
            if(!(*_playerTurn).getResource(Wood) || !(*_playerTurn).getResource(Brick) || !(*_playerTurn).getResource(Sheep) || !(*_playerTurn).getResource(Wheat)){
                std::cout << _playerTurn->getName() << ": " << "there is not enuogh resources to build settlement" << std::endl;
                return false; 
            }
            }
            _board.placeSettlement(row, col, side, (*_playerTurn).getId());
            if(!isFirstTurn){
            (*_playerTurn).addVictoryPoint();
            (*_playerTurn).removeResource(Wood, 1);
            (*_playerTurn).removeResource(Brick, 1);
            (*_playerTurn).removeResource(Sheep, 1);
            (*_playerTurn).removeResource(Wheat, 1);
            }
            return true;

        }
        bool Game::placeCity(size_t row, size_t col, size_t side){
            if((*_playerTurn).getResource(Ore)<3|| (*_playerTurn).getResource(Wheat)<2){
                std::cout << _playerTurn->getName() << ": " << "there is not enuogh resources to build city" << std::endl;
                return false; 
            }
            _board.upgradeToCity(row, col, side, (*_playerTurn).getId());
            (*_playerTurn).addVictoryPoint();
            (*_playerTurn).removeResource(Ore, 3);
            (*_playerTurn).removeResource(Wheat, 2);
            return true;

        }
        bool Game::placeRoad(size_t row, size_t col, size_t side){
            if(!isFirstTurn && !devCard){
            if(!(*_playerTurn).getResource(Wood) || !(*_playerTurn).getResource(Brick)){
                std::cout << _playerTurn->getName() << ": " << "there is not enuogh resources to build road" << std::endl;
                return false;
                 }
            }
            _board.placeRoad(row, col, side, (*_playerTurn).getId());
            if(!isFirstTurn && !devCard){
            (*_playerTurn).removeResource(Wood, 1);
            (*_playerTurn).removeResource(Brick, 1);
            devCard = false;
            }
            return true;
        }

        bool Game::buyDevCard(){
            if(!(*_playerTurn).getResource(Sheep) || !(*_playerTurn).getResource(Ore) || !(*_playerTurn).getResource(Wheat)){
                std::cout << _playerTurn->getName() << ": " << "there is not enuogh resources to buy development card" << std::endl;
                return false;
                }
                DevCard c = devCardGame[cardPointer];
                std::string cardStr;
                switch (c) {
                case Knight: cardStr = "Knight"; break;
                case YearOfPlenty: cardStr = "YearOfPlenty"; break;
                case RoadBuilding: cardStr = "RoadBuilding"; break;
                case Monopoly: cardStr = "Monopoly"; break;
                case VictoryPoint: cardStr = "VictoryPoint";
                      (*_playerTurn).addVictoryPoint();
                       break;
                }
                std::cout << (*_playerTurn).getName() << " get " << cardStr << std::endl;
                (*_playerTurn).addDevCard(c);
                cardPointer++;
                return true;
        }

        bool Game::playDevCard(DevCard card){
            if(!(*_playerTurn).getDevCard(card)){
                 std::cout << _playerTurn->getName() << ": " << "you are not have this development card" << std::endl;
                return false;
            }
            switch (card) {
                case Knight: 
                 std::cout << _playerTurn->getName() << ": " << "you open Knight card" << std::endl;
                 (*_playerTurn).addKnight();
                 if((*_playerTurn).getKnight() == 3 && (*_playerTurn).getKnight() > maxKnight){
                    maxKnight = 3;
                    knightsOwner = _playerTurn;
                    (*_playerTurn).addVictoryPoint();
                    (*_playerTurn).addVictoryPoint();
                 }
                 if((*_playerTurn).getKnight() > maxKnight && (*_playerTurn).getKnight() > 3){
                    maxKnight = (*_playerTurn).getKnight();
                    (*knightsOwner).subtractPoints();
                    (*knightsOwner).subtractPoints();
                    knightsOwner = _playerTurn;
                 }
                 (*_playerTurn).removeDevCard(card, 1);
                 break;
                 
                case YearOfPlenty: 
                  std::cout << _playerTurn->getName() << ": " << " Take any 2 resource cards from the bank" << std::endl;
                  int a, b;
                 std::cout << _playerTurn->getName() << ": " << "choose the first resource: ";
                 std::cin >> a;
                 (*_playerTurn).addResource((Resource)a);
                 std::cout << _playerTurn->getName() << ": " << "choose the second resource: ";
                 std::cin >> b;
                 (*_playerTurn).addResource((Resource)b);
                  (*_playerTurn).removeDevCard(card, 1);
                  break;

                case RoadBuilding:
                devCard = true;
                 std::cout << _playerTurn->getName() << ": " << "Take 2 road pieces from the supply and place them on the board" << std::endl;
                 int row, col, side;
                 std::cout << _playerTurn->getName() << ": " << "choose tile and size for the first road: ";
                 std::cin >> row >> col >> side;
                 placeRoad(row, col, side);
                 devCard = true;
                 std::cout << _playerTurn->getName() << ": " << "choose tile and size for the second road: ";
                 std::cin >> row >> col >> side;
                 placeRoad(row, col, side);
                  (*_playerTurn).removeDevCard(card, 1);
                  break;

                case Monopoly:
                   std::cout << _playerTurn->getName() << ": " <<  "Choose 1 resource type from the resources you have on hand. All other players must give you all their cards of that type" << std::endl;
                   int c;
                   std::cout << _playerTurn->getName() << ": " << "choose the resource: ";
                   std::cin >> c;
                   int sum;
                   int t1, t2, t3;
                   t1 = _p1.getResource((Resource)c);
                   t2 = _p2.getResource((Resource)c);
                   t3 = _p3.getResource((Resource)c);
                   sum = t1 +t2 +t3;
                   _p1.removeResource((Resource)c, t1);
                   _p2.removeResource((Resource)c, t2);
                   _p3.removeResource((Resource)c, t3);
                   while (sum)
                   {
                    (*_playerTurn).addResource((Resource)c);
                    sum--;
                   }
                   std::cout << _playerTurn->getName() << ": " << "you have now " << t1+t2+t3 << std::endl;
                   
                    (*_playerTurn).removeDevCard(card, 1);
                    break; 
                   

                case VictoryPoint:
                 std::cout << _playerTurn->getName() << ": " << "there is not what to do" << std::endl;
                 break;
                }
                return true;
        }

        void Game::rollDice(){
            int dice = rand()%12 + 1;
            std::cout << "dice rolls: " << dice << std::endl;
            if(dice == 7){
                if(_p1.numOfResourcesCards()>7){
                    removeCards(_p1);
                }
                if(_p2.numOfResourcesCards()>7){
                    removeCards(_p2);
                }
                if(_p1.numOfResourcesCards()>7){
                    removeCards(_p2);
                }
                return;  
            }
            //give resources to the players by the number of the dices
            for (size_t i = 0; i < 5; i++)
            {
                for (size_t j = 0; j < 5; j++)
                {
                    if(_board.getTiles()[i][j].getNumber() == dice){
                        Tile& t = _board.getTiles()[i][j];
                        for (size_t p = 0; p < 6; p++)
                        {
                            Node& n = t.getNode(p);
                            if(n.hasSettlement() || n.hasCity()){
                                switch (n.getPlayer())
                                {
                                case 1:
                                    _p1.addResource(t.getResource());
                                     if(n.hasCity()){_p1.addResource(t.getResource());}
                                    break;
                                case 2:
                                    _p2.addResource(t.getResource());
                                     if(n.hasCity()){_p2.addResource(t.getResource());}
                                    break;   
                                case 3:
                                    _p3.addResource(t.getResource());
                                     if(n.hasCity()){_p3.addResource(t.getResource());}
                                    break;    
                                
                                default:
                                    break;
                                }   

                            }
                        }
                        

                    }
                }
                
            }
            
        }
       void Game::printBoard(){
       for (size_t i = 0; i < 5; i++)
       {
         for (size_t j = 0; j < 5; j++)
         {
            if(_board.getTiles()[i][j].getNumber()){
            Tile& t = _board.getTiles()[i][j];
            std::cout << "("<< i<< "," << j << "):" << getResourceName(t.getResource()) << " " << t.getNumber() << " ";
            
         }
         }
         std::cout << std::endl;
       }
       }

       Player& Game::getKnightOwner(){
        return *knightsOwner;
       }

       int Game::getMaxKnight(){
        return maxKnight;
       }

       bool Game::isGameOver(){
        int t1, t2, t3;
        t1 = _p1.getVictoryPoints();
        t2 = _p2.getVictoryPoints();
        t3 = _p3.getVictoryPoints();
        if(t1==10 || t2==10 || t3==10){return true;}
        return false;
       }

       void Game::removeCards(Player& p){
            int numCards = p.numOfResourcesCards();
            int res;
            std::cout << p.getName() << ": you have " << numCards << " cards" << std::endl;
            p.printResource();
            while(p.numOfResourcesCards() > numCards/2)
            {
                std::cout << p.getName() << ": choose card to remove:" << std::endl;
                std::cin >> res;
                p.removeResource((Resource)res, 1);
            }
            std::cout << "your cards now: " << std::endl;
            p.printResource();
       }


       void Game::trade(Resource give, int num1, Resource get, int num2){
            int accept = 0;
            if(this->_playerTurn->getResource(give) < num1){
                std::cerr << "your seggestion is not possible" << std::endl;
                return;
            }
            std::cout << _playerTurn->getName() << " suggest " << num1 << " " << getResourceName(give) << " by " << num2 << " " << getResourceName(get) << std::endl; 
            //ask player one
            if(_playerTurn->getId() != 1 && !accept){
                std::cout << "if " << _p1.getName() << " accept, press 1. else, press 0" << std::endl;
                std::cin >> accept;
                if(accept){
                    if(_p1.getResource(give) < num1){
                    std::cerr << "this trade is not possible" << std::endl;
                    }
                    else{
                        _playerTurn->removeResource(give, num1);
                        for(int i=0;i<num2;i++){_playerTurn->addResource(get);}
                        _p1.removeResource(get, num2);
                        for(int i=0;i<num1;i++){_p1.addResource(give);}
                        std::cout <<  _playerTurn->getName() << " trade with " << _p1.getName() << std::endl;
                    }
                }
            }
            //ask player two
            if(_playerTurn->getId() != 2 && !accept){
                std::cout << "if " << _p2.getName() << " accept, press 1. else, press 0" << std::endl;
                std::cin >> accept;
                if(accept){
                    if(_p2.getResource(give) < num1){
                    std::cerr << "this trade is not possible" << std::endl;
                    }
                    else{
                        _playerTurn->removeResource(give, num1);
                        for(int i=0;i<num2;i++){_playerTurn->addResource(get);}
                        _p2.removeResource(get, num2);
                        for(int i=0;i<num1;i++){_p2.addResource(give);}
                        std::cout <<  _playerTurn->getName() << " trade with " << _p2.getName() << std::endl;
                    }
                }
            }
            //ask player three
            if(_playerTurn->getId() != 3 && !accept){
                std::cout << "if " << _p3.getName() << " accept, press 1. else, press 0" << std::endl;
                std::cin >> accept;
                if(accept){
                    if(_p3.getResource(give) < num1){
                    std::cerr << "this trade is not possible" << std::endl;
                    }
                    else{
                        _playerTurn->removeResource(give, num1);
                        for(int i=0;i<num2;i++){_playerTurn->addResource(get);}
                        _p3.removeResource(get, num2);
                        for(int i=0;i<num1;i++){_p3.addResource(give);}
                        std::cout <<  _playerTurn->getName() << " trade with " << _p3.getName() << std::endl;
                    }
                }
            }

       
       }





