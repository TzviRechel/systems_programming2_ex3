// tzvirechel@gmail.com
#pragma once
#include <iostream>
#include <optional>
#include "Node.hpp"
#include "Edge.hpp"
#include "Resource.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include "DevCard.hpp"

class Game {
private:
    Board _board;                // The game board
    Player _p1, _p2, _p3;        // Players in the game
    Player* _playerTurn;         // Reference to the current player's turn
    Player* knightsOwner;        // Reference to the player who owns the largest army
    int maxKnight = 0;           // Maximum number of knight cards held by any player
    int cardPointer = 0;           // Pointer to the next development card
    DevCard devCardGame[25] = {  // Array of development cards in the game
        Knight, YearOfPlenty, Knight, RoadBuilding, VictoryPoint,
        Knight, VictoryPoint, Monopoly, Knight, Knight,
        Knight, Monopoly, Knight, Knight, RoadBuilding,
        Knight, Knight, VictoryPoint, Knight, Knight,
        YearOfPlenty, Knight, Knight, VictoryPoint
    };
  
   public:
    // Constructor to initialize the game with three players
    Game(Player p1, Player p2, Player p3);

    // Method to check if the game is over
    bool isGameOver();

    // Method to get the reference to the current player
    Player& getCurrentPlayer();

    // Move to the next player for the next turn
    void nextPlayer();

    // Roll the dice and Distribute resources based on dice roll
    void rollDice();

    // Get reference to the game board
    Board& getBoard();

    // Distribute resources (for the first turn)
    void giveResources();

    // Place a settlement on the board at specified location
    bool placeSettlement(size_t row, size_t col, size_t side);

    // Place a city on the board at specified location
    bool placeCity(size_t row, size_t col, size_t side);

    // Place a road on the board at specified location
    bool placeRoad(size_t row, size_t col, size_t side);

    // Get player by unique identifier
    Player& getPlayer(int id);

    // Attempt to buy a development card
    bool buyDevCard();

    // Attempt to play a development card
    bool playDevCard(DevCard c);

    // Get the owner of the knight card with the largest army
    Player& getKnightOwner();

    // Get the current maximum number of knight cards owned by any player
    int getMaxKnight();

    //suggests to another players trade cards
    void trade(Resource give, int num1, Resource get, int num2);

    // Print the current state of the board (for debugging purposes)
    void printBoard();

    //call to the player to remove cards when dices is 7
    void removeCards(Player& p);
            
};

    
    
