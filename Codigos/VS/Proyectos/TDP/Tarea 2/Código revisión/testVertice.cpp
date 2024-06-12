#include "Vertice.h"

int main(){
	
    /*Se declaran y crean los vértices mediante el constructor de la clase Vertice.*/ 
    Vertice vertice1(1);
    Vertice vertice2(2); 
    Vertice vertice3(3); 
    
    /*Se declara la variable vecinos_vertice1 con la finalidad de obtener sus vecinos.*/
    set<Vertice*> vecinos_vertice1;
    
    /*Se obtiene los datos de los vértices creados mediante el método obtenerDatoVertice().*/
    cout << "Dato del vértice 1: " << vertice1.obtenerDatoVertice() << endl;
    cout << "Dato del vértice 2: " << vertice2.obtenerDatoVertice() << endl;	
    cout << "Dato del vértice 3: " << vertice3.obtenerDatoVertice() << endl;
    
    /*Se agregan los vecinos de cada vértice cumpliendo la bidireccionalidad (grafo no dirigido).*/
    vertice1.agregarVecino(&vertice2);
    vertice1.agregarVecino(&vertice3);
    vertice2.agregarVecino(&vertice1);
    vertice3.agregarVecino(&vertice1);
    
    /*A la variable vecinos_vertice1 se le asigna el método para obtener sus vértices vécinos.*/
    /*Después, se procede a imprimir sus vecinos.*/
    vecinos_vertice1 = vertice1.obtenerVecinosVertice();
    cout << "Los vecinos del vértice 1 son: "; 
    
    for(Vertice* vertice_vecino: vecinos_vertice1){
    	cout << vertice_vecino->obtenerDatoVertice() << " ";
    }
    cout << endl; 
 
    /*Se hace la comparación de los datos con la función de operador >.*/	   	   
    cout << "Comparación v1 < v2: " << (vertice3 < vertice2 ? "true" : "false") << endl;
    cout << "Comparación v2 < v3: " << (vertice2 < vertice3 ? "true" : "false") << endl;
    
    return 0; 
}
