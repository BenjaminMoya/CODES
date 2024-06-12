#include "Clique.h"

/*
   * Método: Clique
   * Descripción: Método constructor usado para la creación de un Clique con un string 
   * corresponde al nombre del archivo a ser leído.
   * Parámetros de entrada: 	
   *   - nombre_archivo: Nombre del archivo al cual se le aplica la lectura.
   * Salida:
   *   - Clique.		
*/

Clique::Clique(string nombre_archivo){
    int cant_vertices;  
    int vertice1, vertice2; 

    ifstream archivo(nombre_archivo);

    if(!archivo.is_open()){
        cout << "Error al abrir el archivo" << endl;
        exit(EXIT_FAILURE); 
    }

    archivo >> cant_vertices; 
    this->num_vertices = cant_vertices;
    
    vertices.resize(num_vertices, Vertice(0));
    for (int i = 0; i < num_vertices; ++i) {
        vertices[i] = Vertice(i);
    }

    while (archivo >> vertice1 >> vertice2) {
        vertices[vertice1].agregarVecino(&vertices[vertice2]);
        vertices[vertice2].agregarVecino(&vertices[vertice1]);
    }
    
    archivo.close();
}

/*
   * Método: obtenerCantidadVertices
   * Descripción: Método con el cual se obtiene la cantidad de 
   * vértices de un clique. 
   * Parámetros de entrada: 	
   *   - No contiene ningún parámetro de entrada.
   * Salida:
   *   - Corresponde a la cantidad de vértices (int). 		
*/

int Clique::obtenerCantidadVertices(){
    return num_vertices;	
}

/*
   * Método: bron_kerbosch
   * Descripción: Método que implementa el algoritmo Bron-Kerbosch para encontrar el clique máximo en un grafo.
   * Este algoritmo utiliza una técnica de backtracking combinada con poda basada en una heurística
   * codiciosa (greedy). La poda se realiza usando una cota superior calculada como el mínimo entre
   * la cantidad de colores obtenidos por el método greedyColoring y la suma de los tamaños de P1 y R1. 
   * Parámetros de entrada: 	
   *   - R: Conjunto de vértices (Set<Vertice*>) que ya forman parte del clique actual.
   *   - P: Conjunto de vértices (Set<Vertice*>) que aún pueden ser añadidos al clique actual.
   *   - X: Conjunto de vértices (Set<Vertice*>) que ya han sido considerados y no deben 
   	    ser añadidos al clique actual.
   * Salida:
   *   - void, sin embargo el resultado se almacena en el atributo clique_maximo de la clase Clique.
*/

void Clique::bron_kerbosch(set<Vertice*>& R, set<Vertice*>& P, set<Vertice*>& X){
    if(P.empty() && X.empty()){
    	if(R.size() > clique_maximo.size()){
    	   clique_maximo = R;	
    	}
    	
    	return; 
    }

    set<Vertice*> P_nuevo(P);
    set<Vertice*> X_nuevo(X);
    
    Vertice* pivote = *P_nuevo.begin();
    set<Vertice*> vecinos_pivote = pivote->obtenerVecinosVertice();
    
    set<Vertice*> P_pivote_sin_vecinos;
    set_difference(P_nuevo.begin(), P_nuevo.end(), vecinos_pivote.begin(), vecinos_pivote.end(), inserter(P_pivote_sin_vecinos, P_pivote_sin_vecinos.begin()));

    for(Vertice* vertice: P_pivote_sin_vecinos){
        set<Vertice*> R1(R);
        R1.insert(vertice);

        set<Vertice*> vecinos = vertice->obtenerVecinosVertice();
        set<Vertice*> P1;
        set_intersection(P_nuevo.begin(), P_nuevo.end(), vecinos.begin(), vecinos.end(), inserter(P1, P1.begin()));

        set<Vertice*> X1;
        set_intersection(X_nuevo.begin(), X_nuevo.end(), vecinos.begin(), vecinos.end(), inserter(X1, X1.begin()));
        
        int cantidad_colores = greedyColoring(P1, R1);
        int cota_superior_clique = P1.size() + R1.size();
	
	if(min(cantidad_colores, cota_superior_clique) > obtenerTamanoCliqueMaximo()){  
	   bron_kerbosch(R1, P1, X1);	
	}

        P_nuevo.erase(vertice);
        X_nuevo.insert(vertice);
        
    }

}

/*
   * Método: vertices_vecinos
   * Descripción: Método con el cual se obtiene los vértices vecinos
   * de un vértice determinado. 
   * Parámetros de entrada: 	
   *   - vertice: Corresponde a un vértice cualquiera de la clase Vertice.
   * Salida:
   *   - Corresponde a los vecinos del vértice (set<Vertice*>). 		
*/

set<Vertice*> Clique::vertices_vecinos(const Vertice& vertice) const{
    return vertice.obtenerVecinosVertice();
}

/*
   * Método: obtenerTamañoCliqueMaximo
   * Descripción: Método con el cual se obtiene el tamaño 
   * del clique máximo. 
   * Parámetros de entrada: 	
   *   - No contiene ningún parámetro de entrada.
   * Salida:
   *   - Corresponde a la cantidad de vértices del clique máximo (int). 		
*/

int Clique::obtenerTamanoCliqueMaximo(){
    
    return clique_maximo.size(); 	
}

/*
   * Método: greedyColoring
   * Descripción: Método que implementa una heurística de coloreado greedy para determinar el
   * número de colores necesarios para colorear un subgrafo formado por los vértices en los 
   * conjuntos P1 y R1. Asigna colores a los vértices de forma que dos vértices adyacentes no 
   * tengan el mismo color y calcula el número máximo de colores usados.
   * Parámetros de entrada: 	
   *   - P1: Conjunto de vértices (Set<Vertice*>)que aún pueden ser añadidos al clique en la búsqueda actual.
   *   - R1: Conjunto de vértices (Set<Vertice*>) que ya forman parte del clique en la búsqueda actual.
   * Salida:
   *   - Corresponde a la cantidad de colores (int) necesarios para colorear los vértices 
   *     del subgrafo formado por los conjuntos P1 y R1, lo cual es igual al índice del 
   *     máximo color asignado en el grafo, sumado con 1.
*/

int Clique::greedyColoring(set<Vertice*>& P1, set<Vertice*>& R1) {
    set<Vertice*> union_P1_R1;
    set_union(P1.begin(), P1.end(), R1.begin(), R1.end(), inserter(union_P1_R1, union_P1_R1.begin()));

    int maximo_vertice = -1;
    for (const Vertice* vertice : union_P1_R1) {
        maximo_vertice = max(maximo_vertice, vertice->obtenerDatoVertice());
    }
    vector<int> color(maximo_vertice + 1, -1);

    for (Vertice* vertice : union_P1_R1) {
        set<int> colores_no_disponibles;
        int dato_vertice = vertice->obtenerDatoVertice();

        for (Vertice* vecino : vertices_vecinos(*vertice)) {
            int dato_vecino = vecino->obtenerDatoVertice();
            if (union_P1_R1.find(vecino) != union_P1_R1.end() && color[dato_vecino] != -1) {
                colores_no_disponibles.insert(color[dato_vecino]);
            }
        }

        int color_vertice = 0;
        while (colores_no_disponibles.count(color_vertice) > 0) {
            color_vertice++;
        }

        color[dato_vertice] = color_vertice;
    }

    int maximo_color = *max_element(color.begin(), color.end());

    return maximo_color + 1;
}

/*
   * Método: imprimir_clique
   * Descripción: Método con el cual se imprime el clique máximo
   * de la clase Clique y su tamaño. 
   * Parámetros de entrada: 	
   *   - No existen parámetros de entrada.
   * Salida:
   *   - void. 		
*/ 

void Clique::imprimir_clique(){ 

    for(Vertice* vertice: clique_maximo){
    	cout << vertice->obtenerDatoVertice() << " ";
    }
    
    cout << endl; 
    
    cout << "Tamaño del clique: " << clique_maximo.size();
    cout << endl; 

}

/*
   * Método: obtenerVertice
   * Descripción: Método con el cual el vértice de un clique 
   * mediante su índice en el vector<Vertice*> vertices. 
   * Parámetros de entrada: 	
   *   - indice: Corresponde a un número que representa la posición 
   	del vértice en el vector<Vertice*> vertices.
   * Salida:
   *   - Corresponde a un vértice de la clase Vértice. 		
*/ 

Vertice& Clique::obtenerVertice(int indice){
     return vertices.at(indice);
}

