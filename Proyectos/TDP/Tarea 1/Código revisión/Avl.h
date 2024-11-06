#include "AvlNode.h"

class Avl {
public:
  AvlNode *root;                                // Raiz del arbol
  int height(AvlNode *node);                    // Obtiene la altura del arbol
  int balanceFactor(AvlNode *node);             // Obtiene el factor de balance
  AvlNode *rotateRight(AvlNode *y);             // Se rota a la derecha
  AvlNode *rotateLeft(AvlNode *x);              // Se rota a la izquierda
  AvlNode *balance(AvlNode *node);              // Se balancea el Arbol
  AvlNode *insertNode(AvlNode *node, State *s); // Se inserta un nodo
  AvlNode *removeNode(AvlNode *node, long long int id);   // Se elimina un nodo
  AvlNode *minValueNode(AvlNode *node); // Se obtiene el elemento de menor valor del arbol
  void destroyTree(AvlNode *node); // Se destrulle el arbol
  Avl();                           // Constructor del arbol
  ~Avl();                          // Destructor del arbol
  void push(State *s);             // Inserta un elemento a un arbol
  bool find(State *s); // Verifica si un elemento ya existe en el arbol
  void remove(long long int id); // Se quita un valor del arbol
  int Avlheight(AvlNode *node);
  int countNodes(AvlNode *node);
};
