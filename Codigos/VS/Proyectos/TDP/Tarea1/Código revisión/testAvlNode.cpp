#include "AvlNode.h"
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
  // Se crea un nodo
  AvlNode *n = new AvlNode(e);
  // Se verifica que se haya creado bien el nodo
  n->state->print_board();
  if (n->parent == nullptr && n->left == nullptr && n->right == nullptr) {
    cout << "Se creo correctamente el nodo" << endl;
  }
  return 0;
}