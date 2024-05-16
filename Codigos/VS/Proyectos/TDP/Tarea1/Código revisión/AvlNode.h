#include "State.h"

class AvlNode {
public:
  State *state;          // Valor del nodo
  AvlNode *left;         // Hijo izquierdo
  AvlNode *right;        // Hijo derecho
  AvlNode *parent;       // Padre
  int height;            // Altura a la que se encuentra
  AvlNode(State *state); // Constructor del nodo
  ~AvlNode();            // Destructor del nodo
  void ActHeight();
};