#include "Graph.h"

Graph::Graph(){

    m_adyacency = vector<vector<int>>();
    this->size_m = 0;

}
Graph::Graph(int size_m) {

    m_adyacency = vector<vector<int>>();
    this->size_m = size_m;

}

Graph::Graph(vector<vector<int>> matrix, int size_m) {
    m_adyacency = matrix;
    this->size_m = size_m;
}

set<int>* Graph::vertexNeighbours(int v) {
    set<int>* neighbours = new set<int>;
    for (int i = 0; i < size_m; i++) {
        if (m_adyacency[v][i] == 1) {
            neighbours->insert(i);
        }
    }
    return neighbours;
} 

set<set<int>*> * Graph::BK(set<int> *R,set<int> P, set<int> X , set<set<int>*> *C ) {

  
    if (P.empty() && X.empty()) {

        if(R->size()>Cmax->size()){
            Cmax = R;
        }
        C->insert(R);
        return(C);
    }

    set<int> P_new= P; 
    set<int> X_new= X; 
    set<int> P_iter;

    if(pivot_num == 0){

        pivot_num++;
        int pivot = maxDegree(P);
        set<int> *neighbours = vertexNeighbours(pivot);
        set_difference(P.begin(), P.end(), neighbours->begin(), neighbours->end(), inserter(P_iter, P_iter.end()));
        delete neighbours;

    } else {

        int pivot = *P.begin();
        set<int> *neighbours = vertexNeighbours(pivot);
        set_difference(P.begin(), P.end(), neighbours->begin(), neighbours->end(), inserter(P_iter, P_iter.end()));
        delete neighbours;

    }

    for(auto v : P_iter) {
        
        set<int> *R1 = new set<int>(*R);
        R1->insert(v);

        set<int>* vecinos = vertexNeighbours(v);
        set<int> P1;
        set_intersection(P_new.begin(), P_new.end(), vecinos->begin(), vecinos->end(), inserter(P1, P1.begin()));

        set<int> X1;
        set_intersection(X_new.begin(), X_new.end(), vecinos->begin(), vecinos->end(), inserter(X1, X1.begin()));

        if((R1->size()+P1.size())>=Cmax->size()){

            C = this->BK(R1,P1,X1,C);
        }

        P.erase(v);
        X.insert(v);
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
    file >> size_m;
    m_adyacency.resize(size_m, vector<int>(size_m, 0));

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
    for (int i = 0; i < size_m; i++) {
        for (int j = 0; j < size_m; j++) {
            cout << m_adyacency[i][j] << " ";
        }
        cout << endl;
    }

}


int Graph::degree(int v){

    int grade = 0;
    for (int i = 0; i < m_adyacency.size(); ++i) {
        if (m_adyacency[v][i] == 1) { 
            grade++;
        }
    }
    return grade;

}

int Graph::maxDegree(set<int> P){

    int max = 0;
    for(auto it = P.begin(); it != P.end(); it++){

        if(degree(max) < degree(*it)){

            max = (*it);
        }

    }

    return max;

}

double Graph::density(){

    int n = size_m;
    int m = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (m_adyacency[i][j] == 1) {
                m++;
            }
        }
    }

    // Calcular la densidad
    double max_edges = n * (n - 1) / 2.0;
    double density = m / max_edges;

    return density;
}