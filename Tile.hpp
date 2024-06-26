#pragma once
#include <iostream>
#include "Node.hpp"
#include "Edge.hpp"
#include "Resource.hpp"


class Tile {
private:
    Resource _res;         // Resource type of the tile
    int _number;           // Number associated with the tile for gameplay
    Node nodes[6];         // Nodes on each side of the tile
    Edge edges[6];         // Edges on each side of the tile

public:
    // Default constructor
    Tile();

    // Constructor with specified resource and number
    Tile(Resource res, int number);

    // Returns the resource type of the tile
    Resource getResource();

    // Returns the number associated with the tile
    int getNumber();

    // Sets the node on a specified side of the tile
    void setNode(size_t side, const Node& n);

    // Sets the edge on a specified side of the tile
    void setEdge(size_t side, const Edge& e);

    // Returns a reference to the node on a specified side of the tile
    Node& getNode(size_t side);

    // Returns a reference to the edge on a specified side of the tile
    Edge& getEdge(size_t side);

    // Prints the tile
    void printTile();
};