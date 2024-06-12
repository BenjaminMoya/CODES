#include "Vertice.h"

/*
   * Método: Vertice
   * Descripción: Método constructor usado para la creación de un Vertice con un número que 
   * corresponde a su dato.
   * Parámetros de entrada: 	
   *   - num: Corresponde al dato del vértice que se va a crear.
   * Salida:
   *   - Vertice.		
*/

Vertice::Vertice(int num){
    this->dato = num; 	
}

/*
   * Método: obtenerDatoVertice 
   * Descripción: Método en el cual se obtiene el dato de un vértice.
   * Parámetros de entrada: 	
   *   - No contiene ningún parámetro de entrada.
   * Salida:
   *   - Corresponde al dato del vértice (int).  		
*/

int Vertice::obtenerDatoVertice() const{
    return dato; 	
}

/*
   * Método: obtenerVecinosVertice
   * Descripción: Método con el cual se obtiene los vértices vecinos
   * de un vértice determinado. 
   * Parámetros de entrada: 	
   *   - No contiene ningún parámetro de entrada.
   * Salida:
   *   - Corresponde a los vecinos del vértice (set<Vertice*>). 		
*/

set<Vertice*> Vertice::obtenerVecinosVertice() const{
    return vecinos;
}

/*
   * Método: agregarVecino
   * Descripción: Método con el cual se obtiene los vértices vecinos
   * de un vértice determinado. 
   * Parámetros de entrada: 	
   *   - vertice_vecino: Son los vecinos de un determinado vértice (Vertice*).
   * Salida:
   *   - void. 		
*/

void Vertice::agregarVecino(Vertice* vertice_vecino){
    vecinos.insert(vertice_vecino);	
}

/*
   * Método: operator< 
   * Descripción: Método en el cual se compara el orden 2 vértices distintos 
   * (cuál vértice es mayor) mediante sus datos.  
   * Parámetros de entrada: 	
   *   - otro: Es un segundo vértice para poder establece comparación con el primero
   * 	 de ellos. 
   * Salida:
   *   - Verdadero o Falso (bool). 		
*/

bool Vertice::operator<(const Vertice& vertice1) const {
    return obtenerDatoVertice() < vertice1.obtenerDatoVertice();
}
