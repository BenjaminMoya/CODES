#include "Avl.h"
using namespace std;

Avl::Avl() {
  // Se inicializa el arbol AVL con la raiz en nulo
  root = nullptr;
}

int Avl::height(AvlNode *node) {
  // Se obtiene la altura del nodo
  if (node == nullptr) {
    return 0;
  }
  // Se retorna la altura del nodo
  return node->height;
}

int Avl::balanceFactor(AvlNode *node) {
  // Se obtiene el factor de balance del nodo
  if (node == nullptr) {
    return 0;
  }
  // Se retorna el factor de balance del nodo
  return height(node->left) - height(node->right);
}

AvlNode *Avl::rotateRight(AvlNode *y) {
  // Se realiza la rotacion a la derecha
  AvlNode *x = y->left;
  AvlNode *T2 = x->right;
  x->right = y;
  y->left = T2;
  // Se actualiza la altura de los nodos
  y->height = max(height(y->left), height(y->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  // Se actualizan los padres de los nodos
  if (T2 != nullptr) {
    T2->parent = y;
  }
  // Se retorna el nodo rotado
  x->parent = y->parent;
  y->parent = x;

  return x;
}

AvlNode *Avl::rotateLeft(AvlNode *x) {
  // Se realiza la rotacion a la izquierda
  AvlNode *y = x->right;
  AvlNode *T2 = y->left;
  y->left = x;
  x->right = T2;
  // Se actualiza la altura de los nodos
  x->height = max(height(x->left), height(x->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  // Se actualizan los padres de los nodos
  if (T2 != nullptr) {
    T2->parent = x;
  }
  // Se retorna el nodo rotado
  y->parent = x->parent;
  x->parent = y;

  return y;
}

AvlNode *Avl::balance(AvlNode *node) {
  // Se verifica si el nodo es nulo
  if (node == nullptr) {
    return nullptr;
  }
  // Se actualiza la altura del nodo
  node->height = max(height(node->left), height(node->right)) + 1;
  // Se obtiene el factor de balance del nodo
  int bf = balanceFactor(node);
  // Se verifica si el nodo está balanceado
  if (bf == 0) {
    // No es necesario realizar rotaciones
    return node;
  }

  // Se verifica si el nodo esta balanceado
  if (bf > 1 && balanceFactor(node->left) >= 0) {
    // Se realiza la rotacion a la derecha
    return rotateRight(node);
  }
  // Se verifica si el nodo esta balanceado
  if (bf > 1 && balanceFactor(node->left) < 0) {
    // Se realiza la rotacion a la izquierda y luego a la derecha
    node->left = rotateLeft(node->left);
    return rotateRight(node);
  }
  // Se verifica si el nodo esta balanceado
  if (bf < -1 && balanceFactor(node->right) <= 0) {
    // Se realiza la rotacion a la izquierda
    return rotateLeft(node);
  }
  // Se verifica si el nodo esta balanceado
  if (bf < -1 && balanceFactor(node->right) > 0) {
    // Se realiza la rotacion a la derecha y luego a la izquierda
    node->right = rotateRight(node->right);
    return rotateLeft(node);
  }
  // Se retorna el nodo
  return node;
}

AvlNode *Avl::insertNode(AvlNode *node, State *s) {
  // Se verifica si el nodo es nulo
  if (node == nullptr) {
    return new AvlNode(s);
  }
  // Se verifica si el valor del nodo es mayor al valor del estado
  if (s->id < node->state->id) {
    // Se inserta el nodo en el hijo izquierdo
    AvlNode *leftChild = insertNode(node->left, s);
    // Se actualiza el hijo izquierdo del nodo
    node->left = leftChild;
    // Se actualiza el padre del hijo izquierdo
    leftChild->parent = node;
  } else {
    // Se inserta el nodo en el hijo derecho
    AvlNode *rightChild = insertNode(node->right, s);
    // Se actualiza el hijo derecho del nodo
    node->right = rightChild;
    // Se actualiza el padre del hijo derecho
    rightChild->parent = node;
  }
  // Se balancea el nodo
  return balance(node);
}

AvlNode *Avl::removeNode(AvlNode *node, long long int id) {
  // Se verifica si el nodo es nulo
  if (node == nullptr) {
    return nullptr;
  }
  // Se verifica si el valor del nodo es mayor al valor a eliminar
  if (id < node->state->id) {
    // Se elimina el nodo del hijo izquierdo
    node->left = removeNode(node->left, id);
  }
  // Se verifica si el valor del nodo es menor al valor a eliminar
  else if (id > node->state->id) {
    // Se elimina el nodo del hijo derecho
    node->right = removeNode(node->right, id);
  } else {
    // Se verifica si el nodo tiene un solo hijo
    if (node->left == nullptr || node->right == nullptr) {
      // Se verifica si el hijo izquierdo es nulo
      AvlNode *temp = (node->left != nullptr) ? node->left : node->right;
      // Se verifica si el nodo es nulo
      if (temp == nullptr) {
        // Se elimina el nodo
        temp = node;
        node = nullptr;
      } else {
        // Se actualiza el nodo
        *node = *temp;
      }
      // Se elimina el nodo temporal
      delete temp;
    } else {
      // Se obtiene el sucesor del nodo
      AvlNode *temp = minValueNode(node->right);
      // Se actualiza el nodo
      node->state = temp->state;
      // Se elimina el nodo del hijo derecho
      node->right = removeNode(node->right, temp->state->id);
    }
  }
  // Se verifica si el nodo es nulo
  if (node == nullptr) {
    // Se retorna el nodo
    return node;
  }
  // Se actualiza la altura del nodo
  node->height = 1 + max(height(node->left), height(node->right));
  // Se obtiene el factor de balance del nodo
  int bf = balanceFactor(node);
  if (bf <= 1 && bf >= -1) {
    return node;
  }
  // Se balancea el nodo
  return balance(node);
}

AvlNode *Avl::minValueNode(AvlNode *node) {
  // Se obtiene el nodo con el valor minimo
  AvlNode *current = node;
  // Se itera sobre el nodo
  while (current->left != nullptr) {
    // Se actualiza el nodo
    current = current->left;
  }
  // Se retorna el nodo
  return current;
}

void Avl::push(State *s) {
  // Se inserta el estado en el arbol AVL
  //cout << "Insertando " << s->id << " steps:" << s->steps << " value:" << s->value << endl;
  root = insertNode(root, s);
}

bool Avl::find(State *s) {
  // Se verifica si el estado se encuentra en el arbol AVL
  AvlNode *current = root;
  // Se itera sobre el arbol
  while (current != nullptr) { // esto es busqueda binaria iterativa --> O(log n)
    // Se verifica si el ID del estado se encuentra en el nodo actual
    if (s->equals(current->state)) {
      // Si los IDs son iguales, entonces se verifica si los estados son iguales
        return true;
    }
    // Se actualiza el nodo actual basado en el ID del estado
    if (s->id < current->state->id) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  // Se retorna falso si no se encontró el estado
  return false;
}

void Avl::remove(long long int id) {
  // Se elimina el nodo con el valor indicado
  root = removeNode(root, id);
}

Avl::~Avl() {
  // Se destruye el arbol AVL
  destroyTree(root);
}

void Avl::destroyTree(AvlNode *node) {
  // Se destruye el arbol AVL
  if (node != nullptr) {
    // Se destruyen los hijos del nodo
    destroyTree(node->left);
    destroyTree(node->right);
    // Se destruye el nodo
    delete node;
  }
}

int Avl::Avlheight(AvlNode *node) {
  // Se obtiene la altura del arbol AVL
  if (node == nullptr) {
    return 0;
  }
  int leftHeight = height(node->left);
  int rightHeight = height(node->right);
  return 1 + std::max(leftHeight, rightHeight);
}

int Avl::countNodes(AvlNode *node) {
  if (node == nullptr) {
    return 0;
  }
  // Contar el nodo actual y sumar la cantidad de nodos en los subárboles
  // izquierdo y derecho
  return 1 + countNodes(node->left) + countNodes(node->right);
}