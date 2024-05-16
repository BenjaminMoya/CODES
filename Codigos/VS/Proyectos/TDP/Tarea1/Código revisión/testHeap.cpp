#include "Heap.h"
using namespace std;
int main() {
  // Se crea un heap de tamaño 4
  Heap *heap = new Heap(4);
  // Se crea un estado de tamaño 3 y se inicializan algunos componentes
  State *s = new State(3);
  s->board[0][0] = 6;
  s->board[0][1] = 7;
  s->board[0][2] = 3;
  s->board[1][0] = 4;
  s->board[1][1] = 2;
  s->board[1][2] = 1;
  s->board[2][0] = 5;
  s->board[2][1] = 0;
  s->board[2][2] = 8;
  s->i0 = 2;
  s->j0 = 2;
  s->act_value();
  // Se muestra la heuristica del estado
  cout << s->value << endl;
  // Se agrega el estado al heap
  heap->push(s);
  // Se repite con 2 estados mas
  s = new State(3);
  s->board[0][0] = 1;
  s->board[0][1] = 2;
  s->board[0][2] = 3;
  s->board[1][0] = 4;
  s->board[1][1] = 5;
  s->board[1][2] = 6;
  s->board[2][0] = 7;
  s->board[2][1] = 8;
  s->board[2][2] = 0;
  s->i0 = 2;
  s->j0 = 1;
  s->act_value();
  cout << s->value << endl;
  heap->push(s);
  s = new State(3);
  s->board = new int *[3];
  for (int i = 0; i < 3; i++) {
    s->board[i] = new int[3];
  }
  s->board[0][0] = 1;
  s->board[0][1] = 4;
  s->board[0][2] = 3;
  s->board[1][0] = 2;
  s->board[1][1] = 5;
  s->board[1][2] = 6;
  s->board[2][0] = 0;
  s->board[2][1] = 7;
  s->board[2][2] = 8;
  s->i0 = 1;
  s->j0 = 2;
  s->act_value();
  cout << s->value << endl;
  heap->push(s);
  // Se imprime los estados del heap desde el primer elemento hasta el ultimo
  cout << endl;
  heap->pop()->print_board();
  cout << endl;
  heap->pop()->print_board();
  cout << endl;
  heap->pop()->print_board();
  return 0;
}