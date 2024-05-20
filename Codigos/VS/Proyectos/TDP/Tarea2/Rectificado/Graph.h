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

        int size;
        vector<vector<int>> m_adyacency;
        Graph();
        Graph(int size);
        Graph(vector<vector<int>> matrix, int size);
        void addEdge(int v1, int v2);
        set<set<int>*>* coloring(set<int>* P);
        set<set<int>*>* BK(set<int> *R,set<int> *P, set<int> *X , set<set<int>*> *C );
        set<set<int>*>* BKwcolour(set<int> *R,set<int> *P, set<int> *X , set<set<int>*> *C );
        set<int> vertexNeighbours(int v);
        void read();
        void print();

};