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

        int size_m;
        vector<vector<int>> m_adyacency;
        set<int>* Cmax = new set<int>;
        Graph();
        Graph(int size_m);
        Graph(vector<vector<int>> matrix, int size_m);
        void addEdge(int v1, int v2);
        set<set<int>*>* BK(set<int> *R,set<int> *P, set<int> *X , set<set<int>*> *C);
        int maxNeighbours(set<int> *P);
        set<set<int>*>* coloring(set<int>* P);
        set<set<int>*>* BKv2(set<int> *R, set<int>*P, set<int> *X, set<set<int>*>* C);
        set<set<int>*>* BKv3(set<int> *R,set<int> *P, set<int> *X , set<set<int>*> *C);
        set<int>* vertexNeighbours(int v);
        void read();
        void print();

};