#include "Graph.h"

Graph::Graph(){

    m_adyacency = vector<vector<int>>();
    this->size = 0;

}
Graph::Graph(int size) {

    m_adyacency = vector<vector<int>>();
    this->size = size;

}

Graph::Graph(vector<vector<int>> matrix, int size) {
    m_adyacency = matrix;
    this->size = size;
}

void Graph::addEdge(int v1, int v2){

    m_adyacency[v1][v2] = 1;

}

set<int> *Graph::vertexNeighbours(int v) {
    set<int> *neighbours= new set<int>;
    for (int i = 0; i < size; i++) {
        if (m_adyacency[v][i] == 1) {
            neighbours->insert(i);
        }
    }
    return neighbours;
} 

set<set<int>*> * Graph::BK(set<int> *R,set<int> *P, set<int> *X , set<set<int>*> *C ) {

    if (P->empty() && X->empty()) {
        C->insert(R);
        return(C);
    }

    set<int> *P_new= new set<int>(*P); // esto copia P
    set<int> *X_new= new set<int>(*X); // esto copia X
    set<int> *P_iter = new set<int>(*P);
    map<int, set<int>*> neighbours_sets;

    // Mapear la función en el conjunto
    for (int i = 1; i < P->size(); ++i) {
        neighbours_sets[i] = vertexNeighbours(i);
    }

    auto pivot_neighbours = max_element(neighbours_sets.begin(), neighbours_sets.end(),
        [](const set<int>& set1, const set<int>& set2) {
            return set1.size() < set2.size();
        });

    for(auto v : *P_iter) {
        
        set<int> *R1 = new set<int>(*R);
        R1->insert(v);

        set<int> *vecinos = this->vertexNeighbours(v);
        set<int> *P1 = new set<int>;
        set_intersection(P_new->begin(), P_new->end(), vecinos->begin(), vecinos->end(), inserter(*P1, P1->begin()));

        set<int> *X1 = new set<int>;
        set_intersection(X_new->begin(), X_new->end(), vecinos->begin(), vecinos->end(), inserter(*X1, X1->begin()));
        C = this->BK(R1,P1,X1,C);

        P_new->erase(v);
        X_new->insert(v);
    }
    return C;

}

void Graph::read(){

    cout << "Nombre de archivo:";
    string filename;
    cin >> filename;
    cout << "Leyendo archivo " << filename << endl;
    cout << endl;
    ifstream file(filename);

    if (!file.is_open()) {
        cout<< "Error al abrir el archivo." << endl;
        return;
    }

    // Leer el tamaño del grafo
    file >> size;
    m_adyacency.resize(size, vector<int>(size, 0));

    // Leer las conexiones nodo a nodo y actualizar la matriz de adyacencia
    int v1, v2;
    while (file >> v1 >> v2) {

        m_adyacency[v1][v2] = 1;
        m_adyacency[v2][v1] = 1;

    }

    file.close();
    
}


void Graph::print() {

    cout << "Matriz de adyacencia:\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << m_adyacency[i][j] << " ";
        }
        cout << endl;
    }

}