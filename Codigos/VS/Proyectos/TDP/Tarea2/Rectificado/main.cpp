#include "Graph.h"

int main() {

    Graph *g = new Graph();
    g->read();
    
    set<int> *R = new set<int>;
    set<int> P;
    set<int> X;
    set<set<int>*> *C = new set<set<int>*>;
    for (int i = 0; i < g->size_m; i++) {
        P.insert(i);
    }

    cout << "Cargando Clique..." << endl;
    clock_t start = clock(); //Medicion temporal
    C = g->BK(R,P,X,C);
    clock_t end = clock();
    double elapsed = end - start;
    cout << endl;

    cout << "Clique Maximo" << endl;
    
    set<int> *max_clique = new set<int>;
    size_t max_size = 0;
    int i = 0;

    for (const auto& subset : *C) {
        if (subset->size() > max_size) {
            max_size = subset->size();
            max_clique = subset;
        }
    }

    for (const int& vertex : *max_clique) {
        cout << vertex << " ";
        i++;
    }
    
    cout << endl;
    cout << "Size del clique: " << i << endl;
    cout << endl;
    cout << "Tiempo transcurrido:" << elapsed << " Milisegundos" << endl;
    return 0;
    
}