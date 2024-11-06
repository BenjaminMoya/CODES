#include <iostream>
  
/// vamos a definir la clase State de manera abstracta
class State {
    public:
      int **board; // tablero size x size
      int size;
      // al cargar el archivo busco donde esta el 0
      int i0; //fila del cero
      int j0; // columna del cero
      State *parent;
      int depth;
      State();
      State(int size);
      State(int size, State *parent);
      State(int size, State *parent, int **board);
      bool isSol(); // verifica si es solucion
      ~State();
      void print(); // print recursively
      void print_board();
      State *up();
      State *down();
      State *left();
      State *right();
      State *copy();
      bool equals(State *s); // compara dos estados
      //bool equals(State *s); // compara dos estados

};