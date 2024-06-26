# tzvirechel@gmail.com

CXX=clang++
CXXFLAGS=-std=c++11 -Werror
VALGRIND_FLAGS=-v --leak-check=full --show-leak-kinds=all  --error-exitcode=99

# run: catan
#	./$^

catan: Board.o Tile.o Node.o Edge.o Player.o Game.o main.o
	$(CXX) $(CXXFLAGS) $^ -o catan

test: Board.o Tile.o Node.o Edge.o Player.o Game.o Test.o
	$(CXX) $(CXXFLAGS) $^ -o test	

Board.o: Board.cpp Board.hpp
	$(CXX) $(CXXFLAGS) --compile Board.cpp -o Board.o

Game.o: Game.cpp Game.hpp
	$(CXX) $(CXXFLAGS) --compile Game.cpp -o Game.o

Tile.o: Tile.cpp Tile.hpp
	$(CXX) $(CXXFLAGS) --compile Tile.cpp -o Tile.o

Node.o: Node.cpp Node.hpp
	$(CXX) $(CXXFLAGS) --compile Node.cpp -o Node.o

Edge.o: Edge.cpp Edge.hpp
	$(CXX) $(CXXFLAGS) --compile Edge.cpp -o Edge.o

Player.o: Player.cpp Player.hpp
	$(CXX) $(CXXFLAGS) --compile Player.cpp -o Player.o	
	
main.o: main.cpp Board.hpp Tile.hpp Node.hpp Edge.hpp Player.hpp Game.hpp
	$(CXX) $(CXXFLAGS) --compile main.cpp -o main.o

Test.o: Test.cpp
	$(CXX) $(CXXFLAGS) --compile Test.cpp -o Test.o

valgrind: catan Test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./main 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

clean:
	rm -f *.o catan test

	