#include "Avl.h"
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
  // Se crea un Avl
  Avl *avl = new Avl();
  // Se agrega un estado al Avl
  avl->push(e);
  // Se crea una copia del primer stado
  State *e2 = e;
  // Se crean 3 estados mas y se agregan al Avl
  State *e3 = new State(3);
  State *e4 = new State(3);
  e3->board[0][0] = 1;
  e3->board[0][1] = 2;
  e3->board[0][2] = 8;
  e3->board[1][0] = 4;
  e3->board[1][1] = 7;
  e3->board[1][2] = 6;
  e3->board[2][0] = 5;
  e3->board[2][1] = 3;
  e3->board[2][2] = 0;
  e3->i0 = 2;
  e3->j0 = 2;
  e3->act_value();
  avl->push(e3);
  e4->board[0][0] = 7;
  e4->board[0][1] = 2;
  e4->board[0][2] = 6;
  e4->board[1][0] = 4;
  e4->board[1][1] = 1;
  e4->board[1][2] = 8;
  e4->board[2][0] = 5;
  e4->board[2][1] = 3;
  e4->board[2][2] = 0;
  e4->i0 = 2;
  e4->j0 = 2;
  e4->act_value();
  avl->push(e4);
  cout << "Altura: " << avl->height(avl->root) << endl;
  // Se busca el estado 2 para ver si esta ingresado al Avl
  if (!avl->find(e2)) {
    cout << "No se encontro el estado" << endl;

  } else {
    cout << "Se encontro el estado" << endl;
  }
  return 0;
}