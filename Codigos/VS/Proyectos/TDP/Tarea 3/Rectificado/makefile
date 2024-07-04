FLAGS: -g -O2

all: main 

Simplex.o: Simplex.cpp Simplex.h
	g++ $(FLAGS) -c Simplex.cpp

Node.o: Node.cpp Node.h
	g++ $(FLAGS) -c Node.cpp
	
main: main.cpp Simplex.o Node.o 
	g++ $(FLAGS) main.cpp  Simplex.o Node.o -o main

clean:
	rm -f *.o main