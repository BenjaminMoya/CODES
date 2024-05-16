#include "Avl.h"
#include <iostream>

class Heap {
public:
  State **arr;           // Arreglo para estados
  int capacity;          // Capacidad maxima
  int size;              // Indice del ultimo no ocupado o cantidad de elementos
  Heap(int capacity);    // Constructor del Heap
  ~Heap();               // Destructor del Heap
  void push(State *val); // Ingresa un elemento
  State *pop();          // Obtiene el elemento con menor heuristica
  bool isEmpty();        // Se verifica si el Heap esta vacio
};