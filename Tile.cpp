#include <iostream>
#include "Node.hpp"
#include "Edge.hpp"
#include "Resource.hpp"
#include "Tile.hpp"



Tile::Tile(){
    _res = Resource::None;
    _number = 0;
}

Tile::Tile(Resource res, int number): _res(res), _number(number){
            for (size_t i = 0; i < 6; i++)
            {
                nodes[i] = Node();
                edges[i] = Edge();
            }
            
        }

void Tile::setNode(size_t side, const Node &n){
    if(side < 0 || side > 5){
        throw std::out_of_range("side should be between 0 to 5");
    }
    nodes[side] = n;
}

void Tile::setEdge(size_t side, const Edge &e){
    if(side < 0 || side > 5){
        throw std::out_of_range("side should be between 0 to 5");
    }
    edges[side] = e;
}

Node& Tile::getNode(size_t side){
    if(side == -1){return this->nodes[5];
    if(side == 6){return this->nodes[0];}}
    return this->nodes[side];
}

Edge& Tile::getEdge(size_t side){
    if(side == -1){return this->edges[5];}
    if(side == 6){return this->edges[0];}
    return this->edges[side];
}

int Tile::getNumber(){
    return _number;
}

Resource Tile::getResource(){
    return _res;
}

void Tile::printTile(){
     std::string resourceStr;
    switch (_res) {
        case Resource::Wood: resourceStr = "wood"; break;
        case Resource::Brick: resourceStr = "brick"; break;
        case Resource::Sheep: resourceStr = "sheep"; break;
        case Resource::Wheat: resourceStr = "wheat"; break;
        case Resource::Ore: resourceStr = "ore"; break;
        case Resource::Desert: resourceStr = "desert"; break;
        default: resourceStr = "none"; break;
    }
    std::cout << std::endl;
    std::cout << "            " << nodes[0].getPlayer() << std::endl;
    std::cout << "    /               \\" << std::endl;
    std::cout << "    " << nodes[5].getPlayer() << "     " << resourceStr << "      " << nodes[1].getPlayer() << std::endl;
    std::cout << "    |       " << _number << "        |" << std::endl;
    std::cout << "    " << nodes[4].getPlayer() << "               " << nodes[2].getPlayer() << std::endl;
    std::cout << "     \\             /" << std::endl;
    std::cout << "            " << nodes[3].getPlayer() << std::endl;
}
    


