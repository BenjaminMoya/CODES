#ifndef Clique_h
#define Clique_h

#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <set>
#include <vector>
#include "Vertice.h"

using namespace std;

/*
    * Clase Clique:
    * La clase Vértice se representa por tres elementos, los cuales son 
    * el número de vértices que corresponde a un número entero, un vector de vertice de tipo Vertice
    * que contiene un conjunto de los vértices del grafo y el clique máximo que corresponde
    * a un set<Vertice*> que contiene clique máximo obtenido del grafo representado en el archivo de
    * formato ".txt".	
*/

class Clique{
    private: 
        int num_vertices; 
        vector<Vertice> vertices; 
        set<Vertice*> clique_maximo; 
    
    public:
    	//Constructor.
        Clique(string nombre_archivo);
        
        //Selectores.
        int obtenerCantidadVertices();
        void imprimir_clique();
        Vertice& obtenerVertice(int indice);
        
        //Otros Métodos.
        void bron_kerbosch(set<Vertice*>& R, set<Vertice*>& P, set<Vertice*>& X);
        set<Vertice*> vertices_vecinos(const Vertice& vertice) const;
        int obtenerTamanoCliqueMaximo();
        int greedyColoring(set<Vertice*>& P1, set<Vertice*>& R1);
};

#endif
