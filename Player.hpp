#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Resource.hpp"
#include "DevCard.hpp"

class Player {

private:
    std::string _name;  
    int _id;
    int _victoryPoints;
    int resources[5] = {0}; //array to hold the resources cards
    int developmentCard[5] = {0};
    int openKnights = 0;

public:
    // Constructor to initialize a player with name and id
    Player(std::string name, int id);

    // Returns the current number of victory points
    int getVictoryPoints();

    // Increment victory points by one
    void addVictoryPoint();

    // Returns the unique identifier (id) of the player
    int getId();

    // Returns the name of the player
    std::string getName();

    // Returns the current quantity of a specific resource
    int getResource(Resource res);

    // Increase the quantity of a specific resource by one
    void addResource(Resource res);

    // Decrease the quantity of a specific resource by num units
    void removeResource(Resource res, int num);

    // Print out the current resources cards of the player
    void printResource();

    // Returns the current quantity of a specific development card
    int getDevCard(DevCard card);

    // Increase the quantity of a specific development card by one
    void addDevCard(DevCard card);

    // Decrease the quantity of a specific development card by num units
    void removeDevCard(DevCard card, int num);

    // Increment the count of open knight cards (or similar)
    void addKnight();

    // Returns the current number of open knight cards
    int getKnight();

    // Subtract points from the player's total
    void subtractPoints();

    //Returns the current number of resources cards
    int numOfResourcesCards();
};


