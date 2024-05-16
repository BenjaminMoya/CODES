all: State.o Node.o DLL.o TH.o Puzzle.o main testState testNode testDLL testTH testPuzzle

State.o: State.cpp State.h
	g++ -g -c State.cpp

testState: State.o testState.cpp
	g++ -g  State.o testState.cpp -o testState

Node.o: Node.cpp Node.h
	g++ -g -c Node.cpp

testNode: State.o Node.o testNode.cpp
	g++ -g  State.o Node.o testNode.cpp -o testNode
	
DLL.o: DLL.cpp DLL.h
	g++ -g -c DLL.cpp

testDLL: State.o Node.o DLL.o testDLL.cpp
	g++ -g  State.o  Node.o DLL.o testDLL.cpp -o testDLL

TH.o: TH.cpp TH.h
	g++ -g -c TH.cpp

testTH: State.o Node.o DLL.o TH.o testTH.cpp
	g++ -g State.o Node.o DLL.o TH.o testTH.cpp -o testTH

Puzzle.o: Puzzle.cpp Puzzle.h
	g++ -g -c Puzzle.cpp

testPuzzle: State.o Node.o DLL.o TH.o Puzzle.o testPuzzle.cpp
	g++ -g State.o Node.o DLL.o TH.o Puzzle.o testPuzzle.cpp -o testPuzzle

main: State.o Node.o DLL.o TH.o Puzzle.o main.cpp
	g++ -g  State.o Node.o DLL.o TH.o Puzzle.o main.cpp -o main


