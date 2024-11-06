#include "Graph.h"

int main(){

    Graph *g = new Graph();
    Graph *h = new Graph();
    set<int> P;
    set<int>* C = new set<int>;
    char filename1[12] = "clique2.txt";
    char filename2[12] = "clique3.txt";
    g->read(filename1);
    h->read(filename2);
    for(int i = 0; i < g->getNumberOfVertices(); i++){

        P.insert(i);
    }
    cout << endl;
    cout << "Primer grafo" << endl;
    g->print(),
    cout << endl;
    cout << "Segundo grafo" << endl;
    h->print();
    cout << endl;
    cout << "Grado vertice 0 en el primer grafo" << endl;
    cout << g->degree(0) << endl;
    cout << "Grado vertice 0 en el segundo grafo" << endl;
    cout << h->degree(0) << endl;
    cout << endl;
    cout << "Vertice con el mayor grado en el primer grafo" << endl;
    cout << g->maxDegree(P) << endl;
    cout << "Vertice con el mayor grado en el segundo grafo" << endl;
    cout << h->maxDegree(P) << endl;
    cout << "Vecinos vertice 0 en el segundo grafo:";
    C = h->vertexNeighbors(0);
    for (auto it = C->begin(); it != C->end(); it++){

        cout << *it << " ";
    }
    cout << endl;
    cout << "Densidad del primer grafo" << endl;
    cout << g->density() << endl;
    cout << "Densidad del segundo grafo" << endl;
    cout << h->density() << endl;
    cout << endl;
    return 0;
}