all: Node.o DLL.o Graph.o main

Node.o: Node.cpp Node.h
	g++ -g -c Node.cpp

DLL.o: DLL.cpp DLL.h
	g++ -g -c DLL.cpp

Graph.o: Graph.cpp Graph.h
	g++ -g -c Graph.cpp 

main: Node.o DLL.o Graph.o main.cpp
	g++ -O2 -g Node.o DLL.o Graph.o main.cpp -o main
