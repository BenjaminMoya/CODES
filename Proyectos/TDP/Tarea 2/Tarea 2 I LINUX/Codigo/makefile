all: Graph.o main testGraph

Graph.o: Graph.cpp Graph.h
	g++ -O2 -g -c Graph.cpp 

testGraph: Graph.o testGraph.cpp
	g++ -O2 -g Graph.o testGraph.cpp -o testGraph
	
main: Graph.o main.cpp
	g++ -O2 -g Graph.o main.cpp -o main
