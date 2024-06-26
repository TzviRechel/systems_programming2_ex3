#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Node.hpp"
#include <iostream>
#include <string>
#include "Edge.hpp"
#include "Resource.hpp"
#include "Tile.hpp"
#include "Board.hpp"
#include "Game.hpp"
#include "DevCard.hpp"
using namespace std;

TEST_CASE("Node class tests") {
    SUBCASE("Default constructor") {
        Node node;
        CHECK_FALSE(node.hasSettlement());
        CHECK_FALSE(node.hasCity());
        CHECK_EQ(node.getPlayer(), 0);
    }

    SUBCASE("Set settlement") {
        Node node;
        node.setSettlement(1);
        CHECK(node.hasSettlement());
        CHECK_FALSE(node.hasCity());
        CHECK_EQ(node.getPlayer(), 1);
    }

    SUBCASE("Set city") {
        Node node;
        node.setSettlement(1);
        node.setCity();
        CHECK_FALSE(node.hasSettlement());
        CHECK(node.hasCity());
        CHECK_EQ(node.getPlayer(), 1);
    }

    SUBCASE("Set settlement for different player") {
        Node node;
        node.setSettlement(1);
        node.setSettlement(2);  // This should not change the player
        CHECK_EQ(node.getPlayer(), 1);
    }

    SUBCASE("Set city directly") {
        Node node;
        node.setCity();
        CHECK(node.hasCity());
        CHECK_FALSE(node.hasSettlement());
        CHECK_EQ(node.getPlayer(), 0);  // Player ID should still be 0 as setCity() doesn't set a player
    }
}

TEST_CASE("Edge class tests") {
    SUBCASE("Default constructor") {
        Edge edge;
        CHECK_FALSE(edge.hasRoad());
        CHECK_EQ(edge.getPlayer(), -1);
    }

    SUBCASE("Set road") {
        Edge edge;
        edge.setRoad(1);
        CHECK(edge.hasRoad());
        CHECK_EQ(edge.getPlayer(), 1);
    }

    SUBCASE("Set road for different player") {
        Edge edge;
        edge.setRoad(1);
        edge.setRoad(2);  // This should not change the road or player
        CHECK(edge.hasRoad());
        CHECK_EQ(edge.getPlayer(), 1);
    }

    SUBCASE("Multiple edges") {
        Edge edge1;
        Edge edge2;

        edge1.setRoad(1);
        CHECK(edge1.hasRoad());
        CHECK_EQ(edge1.getPlayer(), 1);

        CHECK_FALSE(edge2.hasRoad());
        CHECK_EQ(edge2.getPlayer(), -1);
    }
}

TEST_CASE("Player class tests") {
    Player player("TestPlayer", 1);

    SUBCASE("Constructor and basic getters") {
        CHECK_EQ(player.getName(), "TestPlayer");
        CHECK_EQ(player.getId(), 1);
        CHECK_EQ(player.getVictoryPoints(), 0);
    }

    SUBCASE("Victory points") {
        player.addVictoryPoint();
        CHECK_EQ(player.getVictoryPoints(), 1);
        player.addVictoryPoint();
        CHECK_EQ(player.getVictoryPoints(), 2);
        player.subtractPoints();
        CHECK_EQ(player.getVictoryPoints(), 1);
    }

    SUBCASE("Resource management") {
        CHECK_EQ(player.getResource(Brick), 0);
        player.addResource(Brick);
        CHECK_EQ(player.getResource(Brick), 1);
        player.addResource(Brick);
        CHECK_EQ(player.getResource(Brick), 2);
        player.removeResource(Brick, 1);
        CHECK_EQ(player.getResource(Brick), 1);
    }

    SUBCASE("Development card management") {
        CHECK_EQ(player.getDevCard(Knight), 0);
        player.addDevCard(Knight);
        CHECK_EQ(player.getDevCard(Knight), 1);
        player.addDevCard(Knight);
        CHECK_EQ(player.getDevCard(Knight), 2);
        player.removeDevCard(Knight, 1);
        CHECK_EQ(player.getDevCard(Knight), 1);
    }

    SUBCASE("Knight management") {
        CHECK_EQ(player.getKnight(), 0);
        player.addKnight();
        CHECK_EQ(player.getKnight(), 1);
        player.addKnight();
        CHECK_EQ(player.getKnight(), 2);
    }

    SUBCASE("Resource card count") {
        CHECK_EQ(player.numOfResourcesCards(), 0);
        player.addResource(Brick);
        player.addResource(Wood);
        player.addResource(Ore);
        CHECK_EQ(player.numOfResourcesCards(), 3);
    }
}

TEST_CASE("Tile class tests") {
    SUBCASE("Default constructor") {
        Tile tile;
        CHECK_EQ(tile.getResource(), None); 
        CHECK_EQ(tile.getNumber(), 0);  // Assuming 0 is the default number
    }

    SUBCASE("Parameterized constructor") {
        Tile tile(Wood, 6);
        CHECK_EQ(tile.getResource(), Wood);
        CHECK_EQ(tile.getNumber(), 6);
    }

    SUBCASE("Node and Edge management") {
        Tile tile(Brick, 8);
        Node node;
        Edge edge;

        // Set and get node
        node.setSettlement(1);
        tile.setNode(0, node);
        CHECK(tile.getNode(0).hasSettlement());
        CHECK_EQ(tile.getNode(0).getPlayer(), 1);

        // Set and get edge
        edge.setRoad(2);
        tile.setEdge(0, edge);
        CHECK(tile.getEdge(0).hasRoad());
        CHECK_EQ(tile.getEdge(0).getPlayer(), 2);

    }

    SUBCASE("Multiple tiles") {
        Tile tile1(Resource::Ore, 3);
        Tile tile2(Resource::Sheep, 4);

        CHECK_EQ(tile1.getResource(), Resource::Ore);
        CHECK_EQ(tile1.getNumber(), 3);
        CHECK_EQ(tile2.getResource(), Resource::Sheep);
        CHECK_EQ(tile2.getNumber(), 4);
    }
}

TEST_CASE("Board class tests") {
    Board board;

    SUBCASE("Board initialization") {
        auto& tiles = board.getTiles();
        CHECK_EQ(tiles.size(), 5);
        for (const auto& row : tiles) {
            CHECK_EQ(row.size(), 5);
        }
    }

    SUBCASE("Place settlement") {
        board.placeSettlement(2, 2, 0, 1);
        auto& tiles = board.getTiles();
        CHECK(tiles[2][2].getNode(0).hasSettlement());
        CHECK_EQ(tiles[2][2].getNode(0).getPlayer(), 1);
    }

    SUBCASE("Place road") {
        board.placeRoad(2, 2, 0, 1);
        auto& tiles = board.getTiles();
        CHECK(tiles[2][2].getEdge(0).hasRoad());
        CHECK_EQ(tiles[2][2].getEdge(0).getPlayer(), 1);
    }

    SUBCASE("Upgrade to city") {
        board.placeSettlement(2, 2, 0, 1);
        board.upgradeToCity(2, 2, 0, 1);
        auto& tiles = board.getTiles();
        CHECK(tiles[2][2].getNode(0).hasCity());
        CHECK_EQ(tiles[2][2].getNode(0).getPlayer(), 1);
    }

    SUBCASE("Update adjacent tiles' nodes") {
        board.placeSettlement(2, 2, 0, 1);
        // Check adjacent tiles (assuming updateTilesNodes is called within placeSettlement)
        auto& tiles = board.getTiles();
        
            CHECK(tiles[1][1].getNode(2).hasSettlement());
            CHECK_EQ(tiles[1][2].getNode(4).getPlayer(), 1);
        
    }

    SUBCASE("Update adjacent tiles' edges") {
        board.placeRoad(2, 2, 0, 1);
        // Check adjacent tiles (assuming updateTilesEdges is called within placeRoad)
        auto& tiles = board.getTiles();
            CHECK(tiles[1][2].getEdge(3).hasRoad());
            CHECK_EQ(tiles[1][2].getEdge(3).getPlayer(), 1);
    }

    SUBCASE("Out of bounds access") {
        CHECK_THROWS(board.placeSettlement(5, 5, 0, 1));
        CHECK_THROWS(board.placeRoad(5, 5, 0, 1));
        CHECK_THROWS(board.upgradeToCity(5, 5, 0, 1));
    }
}
