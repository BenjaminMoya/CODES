all: Graph.o main

Graph.o: Graph.cpp Graph.h
	g++ -g -c Graph.cpp 

main: Graph.o main.cpp
	g++ -O2 -g Graph.o main.cpp -o main
