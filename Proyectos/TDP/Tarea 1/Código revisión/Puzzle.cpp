#include "Puzzle.h"

Puzzle::Puzzle() {
  // Se inicializan los atributos de la clase de manera generica
  size = 0;
  board = nullptr;
  open = new Heap(100);
  all = new Avl();
}

Puzzle::Puzzle(int size) {
  // Se inicializan los atributos de la clase con el tamaño del tablero
  this->size = size;
  board = new int *[size];
  // En este caso el tablero se llena con 0's
  for (int i = 0; i < size; i++) {
    board[i] = new int[size];
    for (int j = 0; j < size; j++) {
      board[i][j] = 0;
    }
  }
  open = new Heap(100);
  all = new Avl();
}

Puzzle::Puzzle(int **tablero, int tamanio) {
  // Se inicializan los atributos de la clase con el tablero y el tamaño del
  // tablero
  size = tamanio;
  board = tablero;
  open = new Heap(100);
  all = new Avl();
}

State *Puzzle::generate_init() {
  // Se genera el estado inicial
  State *e = new State(size, nullptr, board);
  // Se inicializan las variables de la clase State
  e->parent = nullptr;
  e->i0 = -1;
  e->j0 = -1;
  // Se verifica si el tablero esta vacio
  if (board == nullptr) {
    cout << "No se ha cargado el tablero" << endl;
    return nullptr;
  }
  // Se busca el 0 en el tablero
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (board[i][j] == 0) {
        e->i0 = i;
        e->j0 = j;
        return e;
      }
    }
  }
  e->act_value();
  return e;
}

// Algoritmo A* para resolver el puzzle
void Puzzle::solve() {
  // Se genera el estado inicial
  State *e_init = generate_init();
  // Se verifica si se pudo generar el estado inicial
  if (e_init == nullptr) {
    cout << "No se pudo generar el estado inicial" << endl;
    return;
  }
  if (e_init->size == 1) {
    cout << "Encontramos la solucion:" << endl;
    e_init->print();
    cout << "Se realizaron " << e_init->steps << " pasos." << endl;
    return;
  }
  // Se agrega el estado inicial al heap open (por visitar) y al arbol AVL all
  // (todo lo generado)
  open->push(e_init);
  all->push(e_init);
  // Se itera mientras el heap open no este vacio
  while (!open->isEmpty()) {
    // Se obtiene el primer elemento del heap open
    State *e = open->pop();

    // Se verifica si el estado es la solucion
    if (e->isSol()) {
      // Si es solucion, se imprime el camino
      cout << "Encontramos la solucion:" << endl;
      e->print();
      cout << "Se realizaron " << e->steps << " pasos." << endl;
      return;
    }
    // Se generan los estados hijos
    State *e_up = e->up();
    if (e_up != nullptr && !all->find(e_up)) {
      // Si no es nulo y no se ha generado antes, se agrega al heap open y al arbol AVL all
      open->push(e_up);
      all->push(e_up);
    } else {
      // Si ya se genero, se elimina el estado
      if (e_up != nullptr) {
        e_up->~State();
      }
    }

    State *e_down = e->down();
    if (e_down != nullptr && !all->find(e_down)) {
      open->push(e_down);
      all->push(e_down);
    } else {
      if (e_down != nullptr) {
        e_down->~State();
      }
    }

    State *e_left = e->left();
    if (e_left != nullptr && !all->find(e_left)) {
      open->push(e_left);
      all->push(e_left);
    } else {
      if (e_left != nullptr) {
        e_left->~State();
      }
    }

    State *e_right = e->right();
    if (e_right != nullptr && !all->find(e_right)) {
      open->push(e_right);
      all->push(e_right);
    } else {
      if (e_right != nullptr) {
        e_right->~State();
      }
    }
  }
  cout << "No se encontro solucion" << endl;
}