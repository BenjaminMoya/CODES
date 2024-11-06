#include <iostream>

/// vamos a definir la clase State de manera abstracta
class State {
    public:
      int **board; // tablero size x size
      int size;
      State *parent;
      State();
      State(int size);
      State(int size, State *parent);
      State(int size, State *parent, int **board);
      ~State();
      void print();
      /*
      bool isSol(); // verifica si es solucion
      State *up();
      State *down();
      State *left();
      State *right();
      bool equals(State *s); // compara dos estados
    */
};