#include "Graph.h"

int main() {

    Graph *g = new Graph(); //Creacion de objeto grafo
    bool flag = true;
    int j;
    while(flag){

        cout << "1)Ingresar grafo" <<endl;
        cout << "2)Salir" <<endl;
        cin >> j;
        if(j==1){
            g->read();
            int i = 0;
            set<int>* R = new set<int>;
            set<int> P;
            set<int> X;
            set<set<int>*>* C = new set<set<int>*>;
            for(int i = 0; i < g->getNumberOfVertices(); i++){

            P.insert(i);
            }

            cout << "Cargando Clique..." << endl;
            clock_t start = clock(); //Inicio medicion temporal
            C = g->BK(R,P,X,C); //Aplicacion algoritmo de Bron-Kerbosch
            clock_t end = clock(); //Termino medicion temporal
            double elapsedTime = double(end - start)/ CLOCKS_PER_SEC; 
            cout << endl;

            //Si hay cliques en el conjunto C se elige el de mayor tamaño
            if(C->empty()){

                cout << "No hay solucion" << endl;
                return 0;
            } else {

                cout << "Clique Maximo" << endl;
                set<int> *maxClique = new set<int>;
                size_t maxSize = 0;
                for (const auto& subset : *C){

                    if (subset->size() > maxSize){

                        maxSize = subset->size();
                        maxClique = subset;
                    }
                }

                for (const int& vertex : *maxClique){

                    cout << vertex << " ";
                    i++;
                }
            }
            cout << endl;
            cout << "Size del clique: " << i << endl;
            cout << endl;
            cout << "Tiempo transcurrido:" << elapsedTime << " Segundos" << endl;
            cout << "Densidad:" << g->density() << endl; //Medida experimental
            cout << endl;
            delete R;
            delete C;
        } else if(j==2){
            
            cout << endl;
            cout << "Terminando la ejecucion..." << endl;
            flag = false;
        } else {

            cout << endl;
            cout << "Debe ingresar una opcion valida" << endl;
        }
    }
    return 0;
}