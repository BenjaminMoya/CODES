#include "Clique.h"
#include <ctime>

int main(){
    // Se declaran las variables a ser utilizadas en el menú y la lectura del archivo donde está el grafo
    // y posteriormente hace el algoritmo de Bron-Kerbosch, en el cual se obtiene el clique máximo.
    int opcion; 
    string nombre_archivo; 
    
    Clique *clique_nuevo; 
    set<Vertice*> R, P, X;
    
    // Variables para medir el tiempo de ejecución del algoritmo Bron-Kerbosch.
    clock_t tiempo_inicio, tiempo_fin;
    double duracion; 
   	
    do{
    	// Este es el inicio del menú, con las opciones a elegir por el usuario.
    	cout << "Este programa encuentra el clique máximo de un grafo de 50 nodos" << endl; 

    	cout << "Opciones: " << endl; 
   	cout << "1) Encontrar el clique máximo del grafo" << endl;
    	cout << "2) Salir" << endl;

    	cout << endl; 
	
	// Se pide la opción y se escribe 1 (para encontrar el clique máximo) o 2
	// (para salir del menú). Si se escribe otro número devuelve al menú normal.
    	cout << "Seleccione una opción: ";
    	cin >> opcion;
    	
        switch(opcion){
            case 1: 
            	// Se pide el nombre del archivo por entrada y se escribe mediante teclado.
                cout << "Ingrese el nombre del archivo a leer: ";
                cin >> nombre_archivo; 
                
                // Se crea el nuevo_clique con el constructor Clique con el parámetro de entrada
    		// del nombre del archivo que será leído. Después se imprime la cantidad de vértices
    		// del grafo.
                clique_nuevo = new Clique(nombre_archivo);
                
                // Se agregan todos los vértices al conjunto P (Potenciales vértices del grafo).
                for(int i = 0; i < clique_nuevo->obtenerCantidadVertices(); i++){
                    P.insert(&clique_nuevo->obtenerVertice(i));
                }
                
                // Se hace el método de Bron-Kerbosch con el propósito de encontrar el clique máximo y 
                // se mide el tiempo de ejecución de este método para medir su eficiencia algorítmica.
                tiempo_inicio = clock();
                clique_nuevo->bron_kerbosch(R, P, X);
                tiempo_fin = clock();
                
                // Se comprueba si el cliqué máximo tiene solución.
    		// Si tiene solución, se imprime el cliqué máximo con su cantidad de vértices (tamaño del clique).
    		// Además, se imprime el tiempo de ejecución del algoritmo Bron-Kerbosch.
    		// Si no hay solución, se entrega un mensaje de que no existe solución.
                if(clique_nuevo->obtenerTamanoCliqueMaximo() == 0){
                    cout << "El grafo del archivo " << nombre_archivo << " no posee un clique máximo." << endl; 
                }
                
                clique_nuevo->imprimir_clique();
                
                cout << "Tiempo de solución: " << (double)(tiempo_fin - tiempo_inicio) / CLOCKS_PER_SEC << " segundos" << endl; 
                
                cout << endl; 
                break; 

            case 2: 
            	// Mensaje de que se sale del menú y se detiene el programa.
                cout << "Se acaba de salir del programa que encuentra el clique máximo de un grafo" << endl; 
                break; 
                
            default:
            	// Se devuelve al menú normal hasta ingresar una opción válida (1 o 2).
            	cout << "Opción ingresada no válida. Ingrese otra opción" << endl;
            	cout << endl; 
            	break; 
            
        }

    }while(opcion != 2);

    return 0; 
}
