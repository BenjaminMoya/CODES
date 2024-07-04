FLAGS = -g -O2

all: test1 

Simplex.o: Simplex.cpp Simplex.h
	g++ $(FLAGS) -c Simplex.cpp

Node.o: Node.cpp Node.h
	g++ $(FLAGS) -c Node.cpp

Tree.o: Tree.cpp Tree.h
	g++ $(FLAGS) -c Tree.cpp
	
test1: test1.cpp Simplex.o Node.o Tree.o
	g++ $(FLAGS) test1.cpp  Simplex.o Node.o Tree.o -o test1

clean:
	rm -f *.o test1