all: Clique.o Vertice.o testClique testVertice main 

Clique.o: Clique.cpp Clique.h
	g++ -O2 -g -c Clique.cpp

Vertice.o: Vertice.cpp Vertice.h
	g++ -O2 -g -c Vertice.cpp
	
testClique: testClique.cpp Clique.o Vertice.o 
	g++ -O2 -g Vertice.o Clique.o testClique.cpp -o testClique

testVertice: testVertice.cpp Vertice.o 
	g++ -O2 -g Vertice.o testVertice.cpp -o testVertice
	
main: Clique.o Vertice.o main.cpp
	g++ -O2 -g Clique.o Vertice.o main.cpp -o main

clean: 
	rm -f *.o testVertice testClique main
