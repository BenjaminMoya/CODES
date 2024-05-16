#include "State.h"
using namespace std;
int main() {
  // Se crea un estado de tamaño 3 y se inicializan algunos componentes
  State *e = new State(3);
  e->board[0][0] = 1;
  e->board[0][1] = 2;
  e->board[0][2] = 3;
  e->board[1][0] = 4;
  e->board[1][1] = 5;
  e->board[1][2] = 6;
  e->board[2][0] = 7;
  e->board[2][1] = 8;
  e->board[2][2] = 0;
  e->i0 = 2;
  e->j0 = 2;
  e->act_value();
  // Se realizan algunos movimientos
  State *arriba = e->up();
  State *izquierda = arriba->left();
  State *derecha = izquierda->right();
  State *abajo = derecha->down();
  // Se imprime el camino y los pasos realizados
  abajo->print();
  cout << "pasos: " << abajo->steps << endl;
  return 0;
}