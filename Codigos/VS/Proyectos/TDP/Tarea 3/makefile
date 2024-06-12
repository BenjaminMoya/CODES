FLAGS = -g

all: test1 

Simplex.o: Simplex.cpp Simplex.h
	g++ $(FLAGS) -c Simplex.cpp

Node.o: Node.cpp Node.h
	g++ $(FLAGS) -c Node.cpp

test1: test1.cpp Simplex.o Node.o
	g++ $(FLAGS) test1.cpp  Simplex.o Node.o -o test1

clean:
	rm -f *.o test1