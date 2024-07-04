// tzvirechel@gmail.com
#pragma once
#include <iostream>
#include "Player.hpp"

class Edge {
private:
    bool _hasRoad;    // Indicates if the edge has a road
    int _playerID;    // ID of the player who owns the road (if any)

public:
    // Default constructor
    Edge();

    // Returns true if the edge has a road, false otherwise
    bool hasRoad();

    // Returns the ID of the player who owns the road (or 0 if no player owns it)
    int getPlayer();

    // Sets a road on the edge for the specified player
    void setRoad(int playerID);
};

