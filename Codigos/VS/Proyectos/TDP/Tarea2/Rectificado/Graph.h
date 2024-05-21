#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <functional>
#include <vector>
#include <set>
#include <bits/stdc++.h>
using namespace std;

class Graph{

    public:

        //Atributos
        int size_m;
        vector<vector<int>> m_adyacency;
        set<set<int>*>* color_classes = new set<set<int>*>;
        set<int>* Cmax = new set<int>;
        int max_degree = 0;
        //Constructores
        Graph();
        Graph(int size_m);
        Graph(vector<vector<int>> matrix, int size_m);
        //Metodos basicos de caracterizacion de vertices
        set<int>* vertexNeighbours(int v);
        int max_neighbours(set<int> *P);
        int degree(int v);
        set<int>* degreeSet(set<int> *P);
        void maxDegree(set<int> *P);
        //Heuristicas y algoritmos de busqueda de clique maximo
        set<set<int>*>* coloring(set<int> *P);
        set<set<int>*>* coloringWithGrade(set<int>* P);
        //BFS ya que los cliques siosi son de distancia 1 a cualquiera de sus nodo 
        set<set<int>*>* BK(set<int> *R,set<int> *P, set<int> *X , set<set<int>*> *C);
        set<set<int>*>* BKv4(set<int> *R,set<int> *P, set<int> *X , set<set<int>*> *C);
        //Metodos auxiliares
        void read();
        void print();

};