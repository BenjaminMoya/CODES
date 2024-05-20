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
    set<int> *neighbours = new set<int>;
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

    for(auto v : *P_iter) {
        
        set<int> *R1 = new set<int>(*R);
        R1->insert(v);

        set<int> *vecinos = vertexNeighbours(v);
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

set<set<int>*>* Graph::coloring(set<int>* P) {
    set<set<int>*>* colourClasses = new set<set<int>*>;
    set<int>* uncolored = new set<int>(*P);

    while (!uncolored->empty()) {
        set<int>* current = new set<int>;
        set<int> aux;
        set<int>* neighbours = new set<int>;
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

        colourClasses->insert(current);
    }

    delete uncolored; // Liberar la memoria del conjunto no coloreado
    return colourClasses;
}

set<int> *Graph::maxClique(){

    set<int> *P = new set<int>;
    set<int>*C = new set<int>;
    for (int i = 0; i < this->size; i++) {
        P->insert(i);
    }
    BKv2(C,P);
    return this->Cmax;
}

void Graph::BKv2(set<int> *C,set<int> *P){

    set<set<int>*>* color_clasess = coloring(P);
    while(!(color_clasess->empty())){
        for (auto it = color_clasess->begin(); it != color_clasess->end(); it++) {
            for (auto it2 = (*it)->begin(); it2 != (*it)->end(); it2++) {
                if(((C->size())+(color_clasess->size()))<= Cmax->size()){
                    return;
                }
                set<int> *neighbours = vertexNeighbours(*it2);
                set<int> *P1 = new set<int>;
                set_intersection(P1->begin(), P1->end(), neighbours->begin(), neighbours->end(), inserter(*P1, P1->begin()));
                C->insert(*it2);
                if((C->size())>(Cmax->size())){

                    Cmax = C;
                }
                if(!(P1->empty())){

                    BKv2(C,P1);
                }

            }
            color_clasess->erase(*it);
        }
    }
}

/*
set<set<int>*>* Graph::BKWithColoring(set<int> *R, set<int>*P, set<int> *X,set<set<int>*>* C){

    set<set<int>*>* color_clasess = coloring(P);
    if (color_clasess->empty() && X->empty()) {
        C->insert(R);
        return(C);
    }

    set<int> *P_new= new set<int>(*P); // esto copia P
    set<int> *X_new= new set<int>(*X); // esto copia X

    while(!(color_clasess->empty())){

        for (auto it = C->begin(); it != C->end(); it++) {
            for (auto it2 = (*it)->begin(); it2 != (*it)->end(); it2++) {
                if(((C->size())+(color_clasess->size()))<= Cmax->size()){
                    return C;
                }
                set<int> *R1 = new set<int>(*R);
                R1->insert(*it2);
                set<int> *vecinos = vertexNeighbours(*it2);
                set<int> *P1 = new set<int>;
                set_intersection(P_new->begin(), P_new->end(), vecinos->begin(), vecinos->end(), inserter(*P1, P1->begin()));
                set<int> *X1 = new set<int>;
                set_intersection(X_new->begin(), X_new->end(), vecinos->begin(), vecinos->end(), inserter(*X1, X1->begin()));
                if((R->size())>(Cmax->size())){

                    Cmax = R;
                }
                if(!(P1->empty())){

                    BKWithColoring(R,P1,X1,C);
                }
                P_new->erase(*it2);
                X_new->insert(*it2);
                
            }
            color_clasess->erase(*it);
        }

        return(C);
    }
}
*/
/*
set<set<int>*>* Graph::BKWithColoring(set<int> *R, set<int>*P, set<int> *X,set<set<int>*>* C){

    if (P->empty() && X->empty()) {
        C->insert(R);
        return C;
    }

    for (auto it = P->begin(); it != P->end(); ++it) {
        int v = *it;
        set<int> *nextR = new set<int>(*R);
        nextR->insert(v);
        set<int> *nextP = new set<int>;
        set<int> *nextX = new set<int>;

        for (auto pIt = P->begin(); pIt != P->end(); ++pIt) {
            if (m_adyacency[v][*pIt] == 1){
                nextP->insert(*pIt);
            }
        }

        for (auto xIt = X->begin(); xIt != X->end(); ++xIt) {
            if (m_adyacency[v][*xIt] == 1){
                nextX->insert(*xIt);
            }
        }

        auto result = BKWithColoring(nextR, nextP, nextX,C);

        C->insert(result->begin(), result->end());

        delete result;

        P->erase(v);
        X->insert(v);
    }

    return C;
}
*//*
set<set<int>*>* Graph::BKWithColoring(set<int> *R, set<set<int>*>*P, set<int> *X, int maxCliqueSize, set<set<int>*>* C) {

    if (P->empty() && X->empty()) {
        if (R->size() >= maxCliqueSize) {
            maxCliqueSize = R->size();
            C->insert(new set<int>(*R));
        }
        return C;
    }

    set<set<int>*>* colorClasses = coloring(P);

    for (auto it = P->begin(); it != P->end(); ++it) {
        for (auto it2 = (*it)->begin(); it2 != (*it)->end(); ++it2) {
            if (R->size() + P->size() <= maxCliqueSize) {
                return C; // No necesitas seguir explorando esta rama
            }

            set<int>* newR = new set<int>(*R);
            newR->insert(*it2);

            set<int>* newP = new set<int>;
            set<int>* newX = new set<int>;
            set<int>* neighbors = vertexNeighbours(*it2);
            set_intersection(P->begin(), P->end(), neighbors->begin(), neighbors->end(), inserter(*newP, newP->begin()));
            set_intersection(X->begin(), X->end(), neighbors->begin(), neighbors->end(), inserter(*newX, newX->begin()));

            set<set<int>*>* cliqueSet = BKWithColoring(newR, newP, newX, maxCliqueSize,C);
            C->insert(cliqueSet->begin(), cliqueSet->end());

            delete newR;
            delete newP;
            delete newX;
        }
    }

    delete colorClasses;
    return C;
    
}
*/
