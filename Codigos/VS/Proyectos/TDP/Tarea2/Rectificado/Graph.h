#include <iostream>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <bits/stdc++.h>
using namespace std;

class Graph{

    public:

        //Atributos
        int size_m;
        int pivot_num = 0;
        vector<vector<int>> m_adyacency;
        set<int>* Cmax = new set<int>;
        //Constructores
        Graph();
        Graph(int size_m);
        Graph(vector<vector<int>> matrix, int size_m);
        //Metodos basicos de caracterizacion de vertices
        set<int>* vertexNeighbours(int v);
        int degree(int v);
        int maxDegree(set<int> P);
        //Algoritmo de busqueda de clique maximo
        set<set<int>*>* BK(set<int> *R,set<int> P, set<int> X , set<set<int>*> *C );
        //Metodos auxiliares
        void read();
        void print();
        double density();

};