#include "Graph.h"

int main() {

    Graph *g = new Graph();
    g->read();
    set<int> *R = new set<int>;
    set<int> *P = new set<int>;
    set<int> *X = new set<int>;
    set<set<int>*> *C = new set<set<int>*>;
    for (int i = 0; i < g->size; i++) {
        P->insert(i);
    }
    cout << endl;
    cout << "Cargando Clique..." << endl;
    clock_t start = clock(); //Medicion temporal
    C = g->BK(R, P, X, C);
    clock_t end = clock();
    double elapsed = end - start;
    cout << endl;
    cout << "Cliques Maximos" << endl;
    for (auto it = C->begin(); it != C->end(); it++) {
        for (auto it2 = (*it)->begin(); it2 != (*it)->end(); it2++) {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    std::cout << "Tiempo transcurrido:" << elapsed << " Milisegundos" << std::endl;
    return 0;
    
}