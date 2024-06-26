#include <iostream>
#include <exception>
#include "Node.hpp"
#include "Edge.hpp"
#include "Resource.hpp"
#include "Tile.hpp"
#include "Board.hpp"


Board::Board(){
    tiles = {
    {Tile(Resource::Ore, 10), Tile(Resource::Sheep, 2), Tile(Resource::Wood, 9), Tile(Resource::None, 0), Tile(Resource::None, 0)},
    {Tile(Resource::Wheat, 12), Tile(Resource::Brick, 6), Tile(Resource::Sheep, 4), Tile(Resource::Brick, 10), Tile(Resource::None, 0)},
    {Tile(Resource::Wheat, 9), Tile(Resource::Wood, 11), Tile(Resource::Desert, -1), Tile(Resource::Wood, 3), Tile(Resource::Ore, 8)},
    {Tile(Resource::Wood, 8), Tile(Resource::Ore, 3), Tile(Resource::Wheat, 4), Tile(Resource::Sheep, 5), Tile(Resource::None, 0)}, 
    {Tile(Resource::Brick, 5), Tile(Resource::Wheat, 6), Tile(Resource::Sheep, 11), Tile(Resource::None, 0), Tile(Resource::None, 0)}
    };

}
    std::vector<std::vector<Tile>> &Board::getTiles(){
        return this->tiles;
    }


    void Board::placeSettlement(size_t row, size_t column, size_t side, int playerID){
        if(row<0 || row>4 || column<0 || column>4 || side <0 || side>5){
            throw std::invalid_argument("out of bound");   
            }
        Node& n = tiles[row][column].getNode(side);
        //error handle
        if(n.hasSettlement() || n.hasCity()){
            throw std::runtime_error("this node not empty");
        }

        n.setSettlement(playerID);
        updateTilesNodes(row, column, side, playerID);   
    }

    void Board::placeRoad(size_t row, size_t column, size_t side, int playerID){
        if(row<0 || row>4 || column<0 || column>4 || side <0 || side>5){
            throw std::invalid_argument("out of bound");   
            }
        Edge& e = tiles[row][column].getEdge(side);
        //error handle
        if(e.hasRoad()){
            throw std::runtime_error("this edge not empty");
        }

        e.setRoad(playerID);
        updateTilesEdges(row, column, side, playerID);  
    }

    void Board::updateTilesNodes(size_t row, size_t column, size_t side, int playerID){
        Node& n = tiles[row][column].getNode(side);
        switch (side)
        {
        case 0:
            if(!row){break;}
            if(!column && row<3){tiles[row-1][column].setNode(4, n);break;}
            if(row<3){
                tiles[row-1][column].setNode(4, n);
                tiles[row-1][column-1].setNode(2, n);}
            else{
                tiles[row-1][column].setNode(2, n);
                tiles[row-1][column+1].setNode(4, n);}      
            break;
        case 1:
            if(column == 4){break;}
            tiles[row][column+1].setNode(5, n);
            if(!row){break;}
            if(row<3){tiles[row-1][column].setNode(3, n);}
            else{tiles[row-1][column+1].setNode(3, n);}     
            break;
         case 2:
            if(column == 4){break;}
            tiles[row][column+1].setNode(4, n);
            if(row==4){break;}
            if(row<2){tiles[row+1][column+1].setNode(0, n);}
            else{tiles[row+1][column].setNode(0, n);}     
            break;
        case 3:
            if(row == 4){break;}
            if(!column && row>1){tiles[row+1][column].setNode(5, n);break;}
            if(row>1){
                tiles[row+1][column].setNode(5, n);
                tiles[row-1][column-1].setNode(1, n);}
            else{
                tiles[row+1][column].setNode(1, n);
                tiles[row-1][column+1].setNode(5, n);}      
            break;        
        case 4:
            if(!column){
                if(row>1){break;}
                else{tiles[row+1][column].setNode(0, n);}
            }    
            else{
                tiles[row][column-1].setNode(2, n);
                if(row==4){break;}
                if(row<2){tiles[row+1][column].setNode(0, n);}
                else{tiles[row+1][column-1].setNode(0, n);}  
            }    
            break;    
        case 5:
            if(!column){
                if(row<3){break;}
                else{tiles[row-1][column].setNode(3, n);}
            }    
            else{
                tiles[row][column-1].setNode(1, n);
                if(!row){break;}
                if(row<3){tiles[row-1][column-1].setNode(3, n);}
                else{tiles[row-1][column].setNode(5, n);} 
            }     
            break;    
        
        default:
            break;
        }
    }    
    

    void Board::upgradeToCity(size_t row, size_t column, size_t side, int playerID){
        if(row<0 || row>4 || column<0 || column>4 || side <0 || side>5){
            throw std::invalid_argument("out of bound");   
            }
        Node n = tiles[row][column].getNode(side);
        //error handle
        if(!n.hasSettlement()){
            throw std::runtime_error("this node is empty");
        }
         if(n.hasSettlement() && n.getPlayer()!=playerID){
            throw std::runtime_error("this settlement belong to another player");
        }
        tiles[row][column].getNode(side).setCity();

    }

    void Board::updateTilesEdges(size_t row, size_t column, size_t side, int playerID){
        Edge& e = tiles[row][column].getEdge(side);
        switch (side)
        {
        case 0:
            if(!row){break;}
            if(row<3){tiles[row-1][column].setEdge(3, e);}
            else{tiles[row-1][column+1].setEdge(3, e);}
            break;
        case 1:
            if(column == 4){break;}
            tiles[row][column+1].setEdge(4, e);   
            break;
        case 2:
            if(row == 4){break;}
            if(row>1){tiles[row+1][column].setEdge(5, e);}
            else{tiles[row+1][column+1].setEdge(5, e);}
            break;
        case 3:
            if(row == 4){break;}
            if(row > 1 && !column){break;}
            if(row>1){tiles[row+1][column-1].setEdge(0, e);}
            else{tiles[row+1][column].setEdge(0, e);}
            break;
        case 4:
            if(!column){break;}
            tiles[row][column-1].setEdge(1, e);   
            break;
        case 5:
            if(!row){break;}
            if(row<3 && !column){break;}
            if(row<3){tiles[row-1][column-1].setEdge(2, e);}
            else{tiles[row-1][column].setEdge(2, e);}
            break;    

        default:
            break;
        }

    }

    




