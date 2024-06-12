#include "Clique.h"

int main(){

    // Se declaran las variables a ser utilizadas en la lectura del archivo donde está el grafo
    // y posteriormente hace el algoritmo de Bron-Kerbosch, en el cual se obtiene el clique máximo.
    string nombre_archivo; 
    Clique *nuevo_clique; 
    set<Vertice*> R, P, X;
    
    // Se pide el nombre del archivo por entrada y se escribe mediante teclado.
    cout << "Ingrese el archivo a leer para obtener el clique máximo: ";
    cin >> nombre_archivo;
    
    // Se crea el nuevo_clique con el constructor Clique con el parámetro de entrada
    // del nombre del archivo que será leído. Después se imprime la cantidad de vértices
    // del grafo.
    nuevo_clique = new Clique(nombre_archivo); 
    
    cout << "El grafo " << nombre_archivo <<  " contiene " << nuevo_clique->obtenerCantidadVertices() << " vértices" << endl; 
    
    // Se agregan todos los vértices al conjunto P (Potenciales vértices del grafo).
    for(int i = 0; i < nuevo_clique->obtenerCantidadVertices(); i++){
    	P.insert(&nuevo_clique->obtenerVertice(i));
    }
    
    // Se hace el método de Bron-Kerbosch con el propósito de encontrar el clique máximo.
    nuevo_clique->bron_kerbosch(R, P, X); 
    
    // Se comprueba si el cliqué máximo tiene solución.
    // Si tiene solución, se imprime el cliqué máximo con su cantidad de vértices (tamaño del clique).
    // Si no hay solución, se entrega un mensaje de que no existe solución.
    if(nuevo_clique->obtenerTamanoCliqueMaximo() == 0){
    	cout << "El grafo del archivo " << nombre_archivo << " no posee un clique máximo." << endl; 
    }
    
    cout << "Clique máximo: ";
    nuevo_clique->imprimir_clique();

    return 0; 
}
