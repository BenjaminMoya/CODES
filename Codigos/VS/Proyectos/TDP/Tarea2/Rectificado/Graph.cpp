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

set<int> Graph::vertexNeighbours(int v) {
    set<int> neighbours;
    for (int i = 0; i < size; i++) {
        if (m_adyacency[v][i] == 1) {
            neighbours.insert(i);
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

    for(auto v : *P_iter) {
        
        cout << v << endl;
        set<int> *R1 = new set<int>(*R);
        R1->insert(v);

        set<int> vecinos = vertexNeighbours(v);
        set<int> *P1 = new set<int>;
        set_intersection(P_new->begin(), P_new->end(), vecinos.begin(), vecinos.end(), inserter(*P1, P1->begin()));

        set<int> *X1 = new set<int>;
        set_intersection(X_new->begin(), X_new->end(), vecinos.begin(), vecinos.end(), inserter(*X1, X1->begin()));
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

set<set<int>*>* Graph::coloring(set<int>* P) {

    int n = P->size();
    vector<int> P_vec(P->begin(), P->end());
    vector<int> degree(n, 0);

    for (int i = 0; i < n; ++i) {
        degree[i] = vertexNeighbours(P_vec[i]).size();
    }

    vector<pair<int, int>> vertices;
    for (int i = 0; i < n; ++i) {
        vertices.push_back({degree[i], P_vec[i]});
    }
    sort(vertices.begin(), vertices.end(), greater<pair<int, int>>());

    P->clear();
    for (int i = 0; i < n; ++i) {
        P->insert(vertices[i].second);
    }

    int color = 0;
    vector<bool> availableColors(n, true);
    vector<int> colors(n, -1);
    set<set<int>*>* colorClasses;

    for (int i = 0; i < n; ++i) {
        fill(availableColors.begin(), availableColors.end(), true);
        for (int u : vertexNeighbours(vertices[i].second)) {
            auto it = find(P_vec.begin(), P_vec.end(), u);
            if (it != P_vec.end()) {
                int idx = distance(P_vec.begin(), it);
                if (colors[idx] != -1) {
                    availableColors[colors[idx]] = false;
                }
            }
        }
        for (int c = 0; c < n; ++c) {
            if (availableColors[c]) {
                colors[i] = c;
                if (colorClasses->size() <= c) {
                    colorClasses->insert(new set<int>());
                }
                auto it = colorClasses->begin();
                advance(it, c);
                const_cast<set<int>&>(**it).insert(vertices[i].second);
                color = max(color, c + 1);
                break;
            }
        }
    }

    return colorClasses;
}
/*
void bronKerboschWithColoring(Graph& G, set<int>& R, set<int>& P, set<int>& X, int& maxCliqueSize, set<int>& maxClique) {
    if (P.empty() && X.empty()) {
        if (R.size() > maxCliqueSize) {
            maxCliqueSize = R.size();
            maxClique = R;
        }
        return;
    }

    set<set<int>> colorClasses = colorSort(P, G);

    for (const auto& colorClass : colorClasses) {
        for (int v : colorClass) {
            if (R.size() + colorClasses.size() <= maxCliqueSize) {
                return;
            }

            set<int> newR = R;
            newR.insert(v);

            set<int> newP, newX;
            set<int> neighbors = G.getNeighbors(v);
            set_intersection(P.begin(), P.end(), neighbors.begin(), neighbors.end(), inserter(newP, newP.begin()));
            set_intersection(X.begin(), X.end(), neighbors.begin(), neighbors.end(), inserter(newX, newX.begin()));

            bronKerboschWithColoring(G, newR, newP, newX, maxCliqueSize, maxClique);

            P.erase(v); // Directly modifies the original P
            X.insert(v); // Directly modifies the original X
        }
    }
}
*/