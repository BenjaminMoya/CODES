#include "Graph.h"

/*
    * Metodo: Constructor->Graph
    * Descripcion: Metodo que crea objetos de la clase grafo
    * e inicializa sus atributos
    * Parametros: 
    * -Ninguno
    * Retorno: 
    * -void
*/
Graph::Graph(){

    adyacencyMatrix = vector<vector<int>>();
    this->numberOfVertices = 0;
    maximunClique = new set<int>;
}

/*
    * Metodo: getNumberOfVertices->Graph
    * Descripcion: Metodo que retorna el numero de vertices del grafo
    * Parametros: 
    * -Ninguno
    * Retorno: 
    * -int: Numero de vertices del grafo
*/
int Graph::getNumberOfVertices(){

    return numberOfVertices;
}

/*
    * Metodo: vertexNeighbors->Graph
    * Descripcion: Metodo que retorna los vecinos de un vertice
    * Parametros: 
    * -int v: Vertice del cual se desean conocer los vecinos
    * Retorno: 
    * -set<int>*: Conjunto de vecinos del vertice v
*/
set<int>* Graph::vertexNeighbors(int v){

    set<int>* neighbors = new set<int>;
    for (int i = 0; i < numberOfVertices; i++){

        if (adyacencyMatrix[v][i] == 1){
            neighbors->insert(i);
        }
    }

    return neighbors;
} 

/*
    * Metodo: BK->Graph
    * Descripcion: Metodo que implementa el algoritmo de Bron-Kerbosch
    * para encontrar el clique maximo de un grafo 
    * Parametros: 
    * -set<int>* R: Conjunto de vertices que forman el clique actual
    * -set<int> P: Conjunto de vertices que pueden ser agregados al clique
    * -set<int> X: Conjunto de vertices que no pueden ser agregados al clique
    * -set<set<int>*>* C: Conjunto de cliques encontrados
    * Retorno: 
    * -set<set<int>*>*: Conjunto de cliques encontrados

*/
set<set<int>*>* Graph::BK(set<int>* R,set<int> P, set<int> X , set<set<int>*>* C ){

    if (P.empty() && X.empty()){ //Si P y X estan vacios se retorna el conjunto de cliques con el clique actual

        if(R->size()>maximunClique->size()){ //Si el clique actual es mayor que el clique maximo se actualiza

            maximunClique = R;
        }

        C->insert(R);
        return(C);
    }

    set<int> P_new= P; 
    set<int> X_new= X; 
    set<int> P_iter;
    int pivot;

    //Se selecciona el pivote segun el vertice con mayor grado
    pivot = maxDegree(P);
    set<int>* neighborsPivot = vertexNeighbors(pivot);
    set_difference(P.begin(), P.end(), neighborsPivot->begin(), neighborsPivot->end(), inserter(P_iter, P_iter.end()));
    delete neighborsPivot;

    if(P_iter.empty()){ //Si P_iter esta vacio rehace el conjunto con el primer elemento de P como pivote

        pivot = *P.begin();
        set<int>* neighborsPivot = vertexNeighbors(pivot);
        set_difference(P.begin(), P.end(), neighborsPivot->begin(), neighborsPivot->end(), inserter(P_iter, P_iter.end()));
        delete neighborsPivot;
    }

    for(auto v : P_iter){ //Se itera sobre los vertices de P_iter
        
        set<int>* R1 = new set<int>(*R);
        R1->insert(v); //Se agrega el vertice v al clique actual

        set<int>* neighborsV = vertexNeighbors(v);
        set<int> P1; //Se actualiza el conjunto de vertices que pueden ser agregados al clique
        set_intersection(P_new.begin(), P_new.end(), neighborsV->begin(), neighborsV->end(), inserter(P1, P1.begin()));

        set<int> X1; //Se actualiza el conjunto de vertices que no pueden ser agregados al clique
        set_intersection(X_new.begin(), X_new.end(), neighborsV->begin(), neighborsV->end(), inserter(X1, X1.begin()));

        if((R1->size()+P1.size())>=maximunClique->size()){//Si el clique actual mas los vertices restantes es mayor o igual al clique maximo se llama recursivamente

            C = this->BK(R1,P1,X1,C);
        }

        P.erase(v); //Se elimina el vertice v del conjunto de vertices que pueden ser agregados al clique
        X.insert(v); //Se agrega el vertice v al conjunto de vertices que no pueden ser agregados al clique
        delete neighborsV;
    }

    return C; //Si no hay mas vertices en P_iter se retorna el conjunto de cliques
}

/*
    * Metodo: read->Graph
    * Descripcion: Metodo que lee un archivo de texto con la informacion
    * de un grafo y lo almacena en la matriz de adyacencia
    * Parametros: 
    * -Ninguno
    * Retorno: 
    * -void
*/
void Graph::read(){

    cout << "Nombre de archivo:";
    string filename;
    cin >> filename;
    cout << "Leyendo archivo " << filename << endl;
    cout << endl;
    ifstream file(filename);
    if (!file.is_open()){

        cout<< "Error al abrir el archivo." << endl;
        return;
    }

    file >> numberOfVertices;
    adyacencyMatrix.resize(numberOfVertices, vector<int>(numberOfVertices, 0));
    int v1, v2;
    while (file >> v1 >> v2){

        adyacencyMatrix[v1][v2] = 1;
        adyacencyMatrix[v2][v1] = 1;
    }

    file.close();
    return;
}

/*
    * Metodo: read->Graph
    * Descripcion: Metodo que lee un archivo de texto con la informacion
    * de un grafo y lo almacena en la matriz de adyacencia
    * Parametros: 
    * -char* : Nombre del archivo
    * Retorno: 
    * -void
*/
void Graph::read(const char* filename){

    cout << "Leyendo archivo " << filename << endl;
    cout << endl;
    ifstream file(filename);
    if (!file.is_open()){

        cout<< "Error al abrir el archivo." << endl;
        return;
    }

    file >> numberOfVertices;
    adyacencyMatrix.resize(numberOfVertices, vector<int>(numberOfVertices, 0));
    int v1, v2;
    while (file >> v1 >> v2){

        adyacencyMatrix[v1][v2] = 1;
        adyacencyMatrix[v2][v1] = 1;
    }

    file.close();
    return;
}

/*
    * Metodo: print->Graph
    * Descripcion: Metodo que imprime la matriz de adyacencia del grafo
    * Parametros: 
    * -Ninguno
    * Retorno: 
    * -void
*/
void Graph::print(){

    cout << "Matriz de adyacencia:\n";
    for (int i = 0; i < numberOfVertices; i++){
        for (int j = 0; j < numberOfVertices; j++){
            cout << adyacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return;
}

/*
    * Metodo: degree->Graph
    * Descripcion: Metodo que retorna el grado de un vertice
    * Parametros: 
    * -int v: Vertice del cual se desea conocer el grado
    * Retorno: 
    * -int: Grado del vertice v
*/
int Graph::degree(int v){

    int vertexDegree = 0;
    for (int i = 0; i < adyacencyMatrix.size(); ++i){

        if (adyacencyMatrix[v][i] == 1){ 
            vertexDegree++;
        }
    }

    return vertexDegree;
}

/*
    * Metodo: maxDegree->Graph
    * Descripcion: Metodo que retorna el vertice con mayor grado 
    * segun la matriz de adyacencia propia del grafo
    * Parametros: 
    * -set<int> P: Conjunto de vertices
    * Retorno: 
    * -int: Vertice con mayor grado
*/
int Graph::maxDegree(set<int> P){

    int max = 0;
    for(auto it = P.begin(); it != P.end(); it++){

        if(degree(max) < degree(*it)){

            max = (*it);
        }

    }

    return max;
}

/*
    * Metodo: density->Graph
    * Descripcion: Metodo que calcula la densidad de un grafo
    * Parametros: 
    * -Ninguno
    * Retorno: 
    * -double: Densidad del grafo
*/
double Graph::density(){

    int n = numberOfVertices;
    int m = 0;
    for (int i = 0; i < n; ++i){
        for (int j = i + 1; j < n; ++j){

            if (adyacencyMatrix[i][j] == 1){

                m++;
            }
        }
    }
    
    double maxEdges = n * (n - 1) / 2.0;
    double density = m / maxEdges;
    return density;
}