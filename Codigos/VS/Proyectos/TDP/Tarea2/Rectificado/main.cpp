#include "Graph.h"

int main() {

    Graph *g = new Graph();
    g->read();
    
    set<int> *R = new set<int>;
    set<int> *P = new set<int>;
    set<int> *X = new set<int>;
    set<int> *C = new set<int>;
    //set<set<int>*> *C = new set<set<int>*>;
    for (int i = 0; i < g->size; i++) {
        P->insert(i);
    }

    cout << "Cargando Clique..." << endl;

    clock_t start = clock(); //Medicion temporal
    C = g->maxClique();
    clock_t end = clock();
    double elapsed = end - start;
    cout << endl;

    cout << "Clique Maximo" << endl;
    /*
    set<int> *max_clique = new set<int>;
    size_t max_size = 0;
    
    for (const auto& subset : *g->Cmax) {
        if (subset->size() > max_size) {
            max_size = subset->size();
            max_clique = subset;
        }
    }

    for (const int& vertex : *max_clique) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
    for (auto it = (g->Cmax)->begin(); it != (g->Cmax)->end(); it++) {
        cout << *it << " ";
    }
    for (auto it = C->begin(); it != C->end(); it++) {
        for (auto it2 = (*it)->begin(); it2 != (*it)->end(); it2++) {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    */
    cout << "Tiempo transcurrido:" << elapsed << " Milisegundos" << endl;
    return 0;
    
}