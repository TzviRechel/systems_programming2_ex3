// tzvirechel@gmail.com
#pragma once
#include <iostream>
#include "Node.hpp"
#include "Edge.hpp"
#include "Resource.hpp"
#include "Tile.hpp"



class Board {
private:
    // 5x5 tiles representing the game board
    std::vector<std::vector<Tile>> tiles{5, std::vector<Tile>(5)};

public:
    // Constructor to initialize the board
    Board();

    // Returns a reference to the 2D vector of tiles
    std::vector<std::vector<Tile>>& getTiles();

    // Places a settlement on the board at the specified location for a player
    void placeSettlement(size_t row, size_t column, size_t side, int playerID);

    // Places a road on the board at the specified location for a player
    void placeRoad(size_t row, size_t column, size_t side, int playerID);

    // Upgrades a settlement to a city on the board at the specified location for a player
    void upgradeToCity(size_t row, size_t column, size_t side, int playerID);

    // Updates nodes of adjacent tiles affected by a player's action at the specified location
    void updateTilesNodes(size_t row, size_t column, size_t side, int playerID);

    // Updates edges of adjacent tiles affected by a player's action at the specified location
    void updateTilesEdges(size_t row, size_t column, size_t side, int playerID);
};