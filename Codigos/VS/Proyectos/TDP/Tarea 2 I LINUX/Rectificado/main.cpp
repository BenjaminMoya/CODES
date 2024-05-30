#include "Graph.h"

int main() {

    Graph *g = new Graph();
    g->read();
    
    set<int>* R = new set<int>;
    set<int> P;
    set<int> X;
    set<set<int>*>* C = new set<set<int>*>;
    for(int i = 0; i < g->getNumberOfVertices(); i++) {

        P.insert(i);
    }

    cout << "Cargando Clique..." << endl;
    clock_t start = clock(); 
    C = g->BK(R,P,X,C);
    clock_t end = clock(); 
    double elapsedTime = double(end - start)/ CLOCKS_PER_SEC;
    cout << endl;
    cout << "Clique Maximo" << endl;

    set<int> *maxClique = new set<int>;
    size_t maxSize = 0;
    int i = 0;
    for (const auto& subset : *C) {
        if (subset->size() > maxSize) {

            maxSize = subset->size();
            maxClique = subset;
        }
    }

    for (const int& vertex : *maxClique) {
        cout << vertex << " ";
        i++;
    }
    
    cout << endl;
    cout << "Size del clique: " << i << endl;
    cout << endl;
    cout << "Tiempo transcurrido:" << elapsedTime << " Segundos" << endl;
    cout << "Densidad:" << g->density() << endl; //Medida experimental
    return 0;
}