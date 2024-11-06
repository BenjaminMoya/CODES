#include "Heap.h"
#include <iostream>
using namespace std;

class Puzzle {
public:
  int **board;      // Matriz que representa al tablero
  int size;         // Tamanio del tablero
  Heap *open;       // Heap de estados por visitar
  Avl *all;         // Avl con los estados generados
  Puzzle();         // Constructor de un puzzle basico
  Puzzle(int size); // Constructor de un puzzle en base al tamanio del tablero
  Puzzle(int **tablero, int tamanio); // Constructor de un puzzle en base al tablero y su tamanio
  ~Puzzle();        // Destructor del puzzle
  State *generate_init(); // Genera un estado inicial para el puzzle
  void solve(); // Funcion que resuelve el puzzle en base al algoritmo A*
};
