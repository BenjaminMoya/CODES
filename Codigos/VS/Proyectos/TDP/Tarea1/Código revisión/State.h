#include <cmath>
#include <iostream>

class State {
public:
  int **board;
  int size;
  int i0;        // Fila del cero
  int j0;        // Columna del cero
  float value;   // Valor de la heuristica
  State *parent; // Estado padre
  int steps;
  long long int id;
  State();         // Constructor del State basico
  State(int size); // Constructor del State en base al tamanio del tablero
  State(int size, State *parent); // Constructor del State en base a tamanio del tablero y su padre
  State(int size, State *parent,int **board); // Constructor en base al tablero, tamanio y padre
  bool isSol();       // Verifica si es solucion
  ~State();           // Destructor
  void print();       // Imprime el camino de resolucion
  void print_board(); // Imprime el tablero
  // Se realizan los movimientos respectivos
  State *up();
  State *down();
  State *left();
  State *right();
  State *copy();         // Copia un State
  bool equals(State *s); // Compara dos estados
  void act_value();      // Calcula el valor de la heuristica
  void createId();
  void resumen();
};