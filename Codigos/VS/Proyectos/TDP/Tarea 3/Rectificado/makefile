FLAGS: -g -O2

all: main 

Simplex.o: Simplex.cpp Simplex.h
	g++ $(FLAGS) -c Simplex.cpp

Node.o: Node.cpp Node.h
	g++ $(FLAGS) -c Node.cpp

Tree.o: Tree.cpp Tree.h
	g++ $(FLAGS) -c Tree.cpp

main: main.cpp Simplex.o Node.o Tree.o
	g++ $(FLAGS) main.cpp  Simplex.o Node.o Tree.o -o main

clean:
	rm -f *.o main