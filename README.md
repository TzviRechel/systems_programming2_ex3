# Catan Game Implementation
This project is a simplified implementation of Catan in C++, designed for 3 players. It simulates the game mechanics, including board setup, resource management, and player interactions.

## Project Structure

The project consists of several key components:

### Board
The `Board` class represents the game board. It's implemented as a 5x5 grid of Tile objects. Key features include:
- A 2D vector of Tile objects to represent the hexagonal board layout
- Methods for placing settlements, roads, and cities
- Logic for updating adjacent tiles when player actions occur
- Resource distribution based on dice rolls

### Tile
The `Tile` class represents individual hexagonal tiles on the board. Each Tile has:
- A resource type (e.g., Wood, Brick, Ore, etc.)
- A number token (2-12, excluding 7)
- Six Node objects representing the corners of the hexagon
- Six Edge objects representing the sides of the hexagon

Tiles are responsible for:
- Storing their resource type and number
- Managing their associated Nodes and Edges
- Participating in resource production when their number is rolled

### Node
The `Node` class represents intersections where players can build settlements and cities. It includes:
- A player ID to track ownership
- Flags for settlement and city status
- Methods for upgrading from settlement to city

### Edge
The `Edge` class represents the edges between nodes where players can build roads. It includes:
- A player ID to track ownership
- A flag to indicate if a road is present

### Player
The `Player` class manages player data and actions, including:
- Resource cards
- Development cards
- Victory points
- Built structures (settlements, cities, roads)

### Game
The `Game` class orchestrates the game flow and rules. It manages:
- Player turns
- Dice rolling
- Resource distribution
- Building actions
- Trading
- Special actions (e.g., playing development cards)

## Board and Tile Implementation Details

The game board is implemented as a 5x5 grid of Tile objects, which approximates the hexagonal layout of the Catan board. Here's how it works:

1. Board Initialization:
   - The Board constructor creates a 5x5 vector of Tile objects.
   - Resources and number tokens are distributed randomly or according to a predefined setup.

2. Coordinate System:
  -The game board is implemented as a 5x5 grid of Tile objects, which approximates the hexagonal layout of the Catan board. However, not all tiles in this grid are used; the layout is structured as follows:

- The top row has 3 tiles.
- The second row has 4 tiles.
- The third row has 5 tiles.
- The fourth row has 4 tiles.
- The bottom row has 3 tiles.
   

3. Node and Edge Connectivity:
   - Each Tile has 6 Nodes and 6 Edges.
   - The Board class ensures that adjacent Tiles share the appropriate Nodes and Edges.
   - This is achieved by having Tiles in the grid share references to the same Node and Edge objects where they meet.

4. Resource Distribution:
   - When a number is rolled, the Board iterates through all Tiles.
   - Tiles with the rolled number trigger resource production for adjacent settlements and cities.

5. Building Placement:
   - When a player builds a settlement, city, or road, the Board updates the appropriate Node or Edge.
   - It also updates any adjacent Tiles that share that Node or Edge.

This implementation allows for efficient game state management and ensures consistency across the board.
