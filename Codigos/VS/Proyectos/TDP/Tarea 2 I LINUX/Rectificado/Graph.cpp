#include "Graph.h"

Graph::Graph(){

    adyacencyMatrix = vector<vector<int>>();
    this->numberOfVertices = 0;
}

int Graph::getNumberOfVertices(){

    return numberOfVertices;
}

set<int>* Graph::vertexNeighbors(int v){

    set<int>* neighbors = new set<int>;
    for (int i = 0; i < numberOfVertices; i++) {
        if (adyacencyMatrix[v][i] == 1) {
            neighbors->insert(i);
        }
    }

    return neighbors;
} 

set<set<int>*>* Graph::BK(set<int>* R,set<int> P, set<int> X , set<set<int>*>* C ) {

    if (P.empty() && X.empty()) {

        if(R->size()>maximunClique->size()){

            maximunClique = R;
        }

        C->insert(R);
        return(C);
    }

    set<int> P_new= P; 
    set<int> X_new= X; 
    set<int> P_iter;
    int pivot;

    pivot = maxDegree(P);
    set<int>* neighborsPivot = vertexNeighbors(pivot);
    set_difference(P.begin(), P.end(), neighborsPivot->begin(), neighborsPivot->end(), inserter(P_iter, P_iter.end()));
    delete neighborsPivot;

    if(P_iter.empty()) {

        pivot = *P.begin();
        set<int>* neighborsPivot = vertexNeighbors(pivot);
        set_difference(P.begin(), P.end(), neighborsPivot->begin(), neighborsPivot->end(), inserter(P_iter, P_iter.end()));
        delete neighborsPivot;
    }

    for(auto v : P_iter) {
        
        set<int>* R1 = new set<int>(*R);
        R1->insert(v);

        set<int>* neighborsV = vertexNeighbors(v);
        set<int> P1;
        set_intersection(P_new.begin(), P_new.end(), neighborsV->begin(), neighborsV->end(), inserter(P1, P1.begin()));

        set<int> X1;
        set_intersection(X_new.begin(), X_new.end(), neighborsV->begin(), neighborsV->end(), inserter(X1, X1.begin()));

        if((R1->size()+P1.size())>=maximunClique->size()){

            C = this->BK(R1,P1,X1,C);
        }

        P.erase(v);
        X.insert(v);
        delete neighborsV;
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

    file >> numberOfVertices;
    adyacencyMatrix.resize(numberOfVertices, vector<int>(numberOfVertices, 0));
    int v1, v2;
    while (file >> v1 >> v2) {

        adyacencyMatrix[v1][v2] = 1;
        adyacencyMatrix[v2][v1] = 1;
    }

    file.close();
    return;
}

void Graph::print() {

    cout << "Matriz de adyacencia:\n";
    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            cout << adyacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return;
}

int Graph::degree(int v){

    int grade = 0;
    for (int i = 0; i < adyacencyMatrix.size(); ++i) {
        if (adyacencyMatrix[v][i] == 1) { 
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

    int n = numberOfVertices;
    int m = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {

            if (adyacencyMatrix[i][j] == 1) {

                m++;
            }
        }
    }
    
    double max_edges = n * (n - 1) / 2.0;
    double density = m / max_edges;
    return density;
}