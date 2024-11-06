#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <bits/stdc++.h>
using namespace std;

/*
    * Graph class:
    * Clase usada para crear un grafo no dirigido y encontrar su clique maximo
    * El grafo se representa mediante una matriz de adyacencia de tamaño numberOfVertices
*/

class Graph{

    private:
        int numberOfVertices;
        vector<vector<int>> adyacencyMatrix;
        set<int>* maximunClique;
    public:
        //Constructor
        Graph();

        //Getter
        int getNumberOfVertices();

        //Metodos basicos de caracterizacion de vertices
        set<int>* vertexNeighbors(int v);
        int degree(int v);
        int maxDegree(set<int> P);

        //Algoritmo de busqueda de clique maximo
        set<set<int>*>* BK(set<int> *R,set<int> P, set<int> X , set<set<int>*> *C );

        //Otros metodos
        void read();
        void read(const char* filename);
        void print();
        double density();

};