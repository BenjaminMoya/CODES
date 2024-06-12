#ifndef Vertice_h
#define Vertice_h

#include <algorithm>
#include <iostream> 
#include <iterator> 
#include <set> 

using namespace std; 

/*
    * Clase Vertice:
    * La clase Vértice se representa por dos elementos, los cuales son 
    * su dato que corresponde a un número entero y de sus vecinos que corresponde
    * a un set<Vertice*>.
    * Esta clase es usada para crear un vértice mediante su número de vértices
    * y posteriormente para crear los vértices y agregar sus vecinos en el constructor 
    * de la clase Clique. 	
*/

class Vertice{
    private: 
    	int dato;  
    	set<Vertice*> vecinos; 
    
    public: 
    	//Constructor
    	Vertice(int num);
    	
    	//Selectores 
    	int obtenerDatoVertice() const;
    	set<Vertice*> obtenerVecinosVertice() const;
    	
    	//Modificador
    	void agregarVecino(Vertice* vecino);
    	
    	// Otros Métodos
    	bool operator<(const Vertice& vertice1) const;
    	
};

#endif
