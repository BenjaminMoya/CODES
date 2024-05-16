#FLAGS = -O2
FLAGS = -g
all: State.o Heap.o AvlNode.o Avl.o Puzzle.o Cargar_tablero.o testState testHeap testAvlNode testAvl testPuzzle testCargar_tablero main
State.o: State.cpp State.h
	g++ ${FLAGS} -c State.cpp
Heap.o: Heap.cpp Heap.h
	g++ ${FLAGS} -c Heap.cpp State.cpp
	
AvlNode.o: AvlNode.cpp AvlNode.h
	g++ ${FLAGS} -c AvlNode.cpp State.cpp
	
Avl.o: Avl.cpp Avl.h
	g++ ${FLAGS} -c Avl.cpp AvlNode.cpp State.cpp
	
Puzzle.o: Puzzle.cpp Puzzle.h
	g++ ${FLAGS} -c Puzzle.cpp Avl.cpp AvlNode.cpp Heap.cpp State.cpp
	
Cargar_tablero.o: Cargar_tablero.cpp Cargar_tablero.h
	g++ ${FLAGS} -c Cargar_tablero.cpp
	
testState: testState.cpp State.o
	g++ ${FLAGS} State.o testState.cpp -o testState
	
testHeap: testHeap.cpp Heap.o State.o
	g++ ${FLAGS} Heap.o State.o testHeap.cpp -o testHeap
	
testAvlNode: AvlNode.o State.o testAvlNode.cpp
	g++ ${FLAGS} AvlNode.o State.o testAvlNode.cpp -o testAvlNode
	
testAvl: testAvl.cpp Avl.o AvlNode.o State.o
	g++ ${FLAGS} Avl.o AvlNode.o State.o testAvl.cpp -o testAvl
	
testPuzzle: testPuzzle.cpp Puzzle.o Avl.o AvlNode.o Heap.o State.o
	g++ ${FLAGS} Puzzle.o Avl.o AvlNode.o Heap.o State.o testPuzzle.cpp -o testPuzzle
	
testCargar_tablero: testCargar_tablero.cpp Cargar_tablero.o
	g++ ${FLAGS} Cargar_tablero.o testCargar_tablero.cpp -o testCargar_tablero
	
main: Puzzle.o Avl.o AvlNode.o Heap.o State.o Cargar_tablero.o main.cpp
	g++ ${FLAGS} Puzzle.o Avl.o AvlNode.o Heap.o State.o Cargar_tablero.o main.cpp -o main
	
clean:
	rm -f *.o testState testHeap testAvlNode testAvl testPuzzle main