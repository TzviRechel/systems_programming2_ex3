// tzvirechel@gmail.com
#pragma once
#include <iostream>
#include "Player.hpp"


class Node {
private:
    int _playerID;       // ID of the player who owns the node (if any)
    bool _hasCity;       // Indicates if the node has a city
    bool _hasSettlement; // Indicates if the node has a settlement

public:
    // Default constructor
    Node();

    // Returns true if the node has a settlement, false otherwise
    bool hasSettlement();

    // Returns true if the node has a city, false otherwise
    bool hasCity();

    // Returns the ID of the player who owns the node (or 0 if no player owns it)
    int getPlayer();

    // Sets a settlement on the node for the specified player
    void setSettlement(int playerID);

    // Sets a city on the node
    void setCity();
};