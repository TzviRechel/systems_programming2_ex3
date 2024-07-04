// tzvirechel@gmail.com
#include <iostream>
#include <string>
#include "Node.hpp"
#include "Edge.hpp"
#include "Resource.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include "Game.hpp"
#include "DevCard.hpp"
using namespace std;

int main(){

    string player1Name, player2Name, player3Name;

    cout << "Enter the name of the first player: " << endl;
    cin >> player1Name;

    cout << "Enter the name of the second player: " << endl;
    cin >> player2Name;

    cout << "Enter the name of the third player: " << endl;
    cin >> player3Name;

    Player p1(player1Name, 1);
    Player p2(player2Name, 2); 
    Player p3(player3Name, 3);

    Game game(p1, p2, p3);
    cout << "let start the game!" << endl;
    
    cout << "the game board:" << endl;
    
    game.printBoard();

    //player 1 place 2 settlements and 2 roads:
    game.placeSettlement(1,2,4);
    game.placeSettlement(0,0,1);
    game.placeRoad(1,2,3);
    game.placeSettlement(4,1,2);
    game.placeRoad(4,1,2);
    cout<< game.getCurrentPlayer().getName() << " status:" << endl;
    game.getBoard().getTiles()[1][2].printTile();
    game.getBoard().getTiles()[4][1].printTile();
   
    //end turn
    game.nextPlayer();
   
     //player 2 place 2 settlements and 2 roads:
    game.placeSettlement(3,2,1);
    game.placeRoad(3,2,0);
    game.placeSettlement(1,3,2);
    game.placeRoad(1,3,2);
    cout<< game.getCurrentPlayer().getName() << " status:" << endl;
    game.getBoard().getTiles()[3][2].printTile();
    game.getBoard().getTiles()[1][3].printTile();
   
    //end turn
    game.nextPlayer();
   
     //player 3 place 2 settlements and 2 roads:
    game.placeSettlement(0,2,0);
    game.placeRoad(0,2,0);
    game.placeSettlement(2,4,3);
    game.placeRoad(2,4,2);
    cout<< game.getCurrentPlayer().getName() << " status:" << endl;
    game.getBoard().getTiles()[0][2].printTile();
    game.getBoard().getTiles()[2][4].printTile();

    //give resources to the player by their settlement positions
    game.giveResources();
    game.getPlayer(1).printResource();
    game.getPlayer(2).printResource();
    game.getPlayer(3).printResource();

    //start game, player 1 turn
    game.nextPlayer();
   game.rollDice();

   game.getPlayer(1).printResource();
    game.getPlayer(2).printResource();
    game.getPlayer(3).printResource();
    //p1 try to buy dev card
    game.buyDevCard();

    game.nextPlayer();
    game.rollDice();

    game.nextPlayer();
    game.rollDice();

    game.nextPlayer();
    game.rollDice();

    game.nextPlayer();
    game.rollDice();

    game.nextPlayer();
    game.rollDice();

    game.nextPlayer();
    game.rollDice();

    game.nextPlayer();
    game.rollDice();

    game.nextPlayer();
    game.rollDice();

    game.nextPlayer();
    game.rollDice();

    game.nextPlayer();
    game.rollDice();

    game.nextPlayer();
    game.rollDice();
     game.buyDevCard();

      game.nextPlayer();   
     game.rollDice();
     game.buyDevCard();
     

    
     game.nextPlayer(); 
     game.rollDice();

game.getPlayer(1).printResource();
    game.getPlayer(2).printResource();
    game.getPlayer(3).printResource();

     game.trade(Brick, 1, Ore, 1);

     game.getPlayer(1).printResource();
    game.getPlayer(2).printResource();
    game.getPlayer(3).printResource();

     game.buyDevCard();
     try{
     game.playDevCard(RoadBuilding);
     }
        catch (const std::exception &e)
    {
        cout << e.what() << endl;
    }
    game.buyDevCard();

    game.nextPlayer(); 
     game.rollDice();

     game.nextPlayer(); 
     game.rollDice();

     game.nextPlayer(); 
     game.rollDice();

     game.nextPlayer(); 
     game.rollDice();




    //game.playCard();

   

    
    
    

    
    
}