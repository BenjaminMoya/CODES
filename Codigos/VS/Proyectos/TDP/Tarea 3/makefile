all: test1 

Simplex.o: Simplex.cpp Simplex.h
	g++ -c Simplex.cpp

Node.o: Node.cpp Node.h
	g++ -c Node.cpp

Tree.o: Tree.cpp Tree.h
	g++ -c Tree.cpp
	
test1: test1.cpp Simplex.o Node.o Tree.o
	g++ test1.cpp  Simplex.o Node.o Tree.o -o test1

clean:
	rm -f *.o test1