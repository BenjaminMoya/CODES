all: State.o Stack.o Puzzle.o testPuzzle

State.o: State.cpp State.h
	g++ -c State.cpp

Stack.o: Stack.cpp State.h
	g++ -c Stack.cpp

Puzzle.o: Puzzle.cpp Puzzle.h
	g++ -c Puzzle.cpp

testPuzzle: testPuzzle.cpp Puzzle.o
	g++ State.o Stack.o Puzzle.o testPuzzle.cpp -o testPuzzle

clean:
	rm -f *.o testPuzzle
