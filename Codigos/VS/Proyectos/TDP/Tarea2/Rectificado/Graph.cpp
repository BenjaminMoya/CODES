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

set<set<int>*> * Graph::BK(set<int> *R,set<int> *P, set<int> *X , set<set<int>*> *C ) {

    if (P->empty() && X->empty()) {
        C->insert(R);
        return(C);
    }

    set<int> *P_new= new set<int>(*P); // esto copia P
    set<int> *X_new= new set<int>(*X); // esto copia X
    set<int> *P_iter = new set<int>(*P);

    for(auto v : *P_iter) {
        
        set<int> *R1 = new set<int>(*R);
        R1->insert(v);

        set<int>* vecinos = vertexNeighbours(v);
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

int Graph::max_neighbours(set<int> *P){

    int pivot = -1;
    int max_value = 0;
    int i = 0;
    set<int>* aux;
    for(auto it = P->begin(); it != P->end(); it++){

        aux = vertexNeighbours(*it);
        if(max_value < aux->size()){

            pivot = i;
            max_value = aux->size();
        }
        i++;
    }
    
    return pivot;
}

set<set<int>*>* Graph::coloring(set<int> *P) {

    set<set<int>*>* colourClasses = new set<set<int>*>;
    set<int>* uncolored = new set<int>(*P);

    while (!uncolored->empty()) {
        set<int>* current = new set<int>;
        set<int> aux;
        set<int>* neighbours;
        set<int> inter;

        for (auto it = uncolored->begin(); it != uncolored->end(); ++it) {
            aux.insert(*it);
            neighbours = vertexNeighbours(*it);
            inter.clear();
            set_intersection(aux.begin(), aux.end(), neighbours->begin(), neighbours->end(),inserter(inter, inter.begin()));
            if (inter.empty()) {
                current->insert(*it);
            }
        }

        for (auto it = current->begin(); it != current->end(); ++it) {
            uncolored->erase(*it);
        }

        delete neighbours;
        colourClasses->insert(current);

    }

    return colourClasses;

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

set<int> *Graph::degreeSet(set<int> *P){

    set<int>* aux = new set<int>;
    for(auto it = P->begin(); it != P->end(); it++){

        aux->insert(degree(*it));

    }
    return aux;

}

void Graph::maxDegree(set<int> *P){

    for(auto it = P->begin(); it != P->end(); it++){

        if(max_degree < (*it)){

            max_degree = (*it);
        }

    }
    return;

}

set<set<int>*>* Graph::coloringWithGrade(set<int>* P){

    int grade;
    set<int> *aux1 = new set<int>;
    set<set<int>*>*aux2 = new set<set<int>*>;
    for(int i=0;i<size_m;i++){

        grade = degree(i);
        aux1->insert(grade);

    }

    auto it = aux1->begin();
    while (it != aux1->end()) {
        set<int> *temp = new set<int>;
        for (int j=0;j<size_m;j++){

            if(degree(j)==(*it)){

                temp->insert(j);

            }
        }
        aux2->insert(temp);
        ++it;
        
    }

    return aux2;
}

set<set<int>*>* Graph::BKv4(set<int> *R,set<int> *P, set<int> *X, set<set<int>*> *C) {
    
    if (P->empty() && X->empty()) {
        C->insert(R);
        return C;
    }

    int pivot = max_neighbours(P);
    set<int> *neighbours = vertexNeighbours(pivot);
    set<int>* P_iter = new set<int>;
    set_difference(P->begin(), P->end(), neighbours->begin(), neighbours->end(), inserter(*P_iter, P_iter->end()));
    delete neighbours;

    for(int v : *P_iter) {
        
        set<int> *R1 = new set<int>(*R);
        R1->insert(v);

        set<int>* vecinos = vertexNeighbours(v);
        set<int>* P1 = new set<int>;
        set_intersection(P->begin(), P->end(), vecinos->begin(), vecinos->end(), inserter(*P1, P1->begin()));

        set<int>* X1 = new set<int>;
        set_intersection(X->begin(), X->end(), vecinos->begin(), vecinos->end(), inserter(*X1, X1->begin()));

        color_classes = coloring(P1);
        int limit = color_classes->size();

        if((R1->size()+limit) > C->size()){

            if(degree(v)==max_degree){

                C = this->BK(R1,P1,X1,C);
                
            }
        }

        P->erase(v);
        X->insert(v);
    }

    return C;

}