#include "State.h"
using namespace std;

State::State() {
  // Se inicializan componentes de un State de manera generica
  board = nullptr;
  size = 0;
  parent = nullptr;
  i0 = -1;
  j0 = -1;
  value = 0.0;
  steps = 0;
  id = 0;
}

State::State(int size) {
  // Se inicializan los componentes de un State en base al tamaño del tablero
  this->size = size;
  // Se genera un tablero lleno de 0's
  this->board = new int *[size];
  for (int i = 0; i < size; i++) {
    this->board[i] = new int[size];
    for (int j = 0; j < size; j++) {
      this->board[i][j] = 0;
    }
  }
  this->parent = nullptr;
  this->i0 = -1;
  this->j0 = -1;
  this->value = 0.0;
  steps = 0;
  id = 0;
}

State::State(int size, State *parent) {
  // Se inicializan los componentes de un State en base al tamaño del tablero
  this->size = size;
  // Se genera un tablero lleno de 0's
  this->board = new int *[size];
  for (int i = 0; i < size; i++) {
    this->board[i] = new int[size];
    for (int j = 0; j < size; j++) {
      this->board[i][j] = 0;
    }
  }
  // Se indica el State padre del nuevo State
  this->parent = parent;
  this->i0 = -1;
  this->j0 = -1;
  this->value = 0.0;
  steps = 0;
  id = 0;
}

State::State(int size, State *parent, int **board) {
  // Se inicializan los componentes de un State en base a un tablero y su tamaño
  this->size = size;
  // Se genera una copia del tablero ingresado
  this->board = new int *[size];
  for (int i = 0; i < size; i++) {
    this->board[i] = new int[size];
    for (int j = 0; j < size; j++) {
      this->board[i][j] = board[i][j];
    }
  }
  this->parent = parent;
  this->i0 = -1;
  this->j0 = -1;
  this->value = 0.0;
  steps = 0;
  id = 0;
}

void State::createId() {
  // Se genera un id unico para cada State en base al orden de los numeros en el tablero
  long long int valor = 0;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      valor = valor + board[i][j]*pow(10, i*size+j);
    }
  }
  id = valor; 
}


// Calcular la heurística mejorada del estado
void State::act_value() {
  float valor = 0;
  float fails = 0;
  int k = 1;
  int conflictos = 0;

    // Calcular el valor de la distancia total de manhattan
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (board[i][j] != 0) {
        int i2=(board[i][j]-1)/size;
          int j2=(board[i][j]-1)%size;
          valor+=abs(i-i2)+abs(j-j2);

          for (int k = j + 1; k < size; k++) {
            if (board[i][j] > board[i][k] && board[i][k] != 0) {
                conflictos += 2;
            }
          }
          for (int k = i + 1; k < size; k++) {
            if (board[i][j] > board[k][j] && board[k][j] != 0) {
              conflictos += 2;
            }
          }
      }
    }
  }
  // contar errores de posicionamiento de los numeros
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (board[i][j] != (k%(size*size)))  {
                    fails++;
                }
            k++;
    }
  }



  // Actualizar el valor de la heurística del estado
  //this->value =  0.08*valor/size + steps*0.0356/size +0.05*conflictos/size+0.12*fails; mejor
  this->value =  0.08*valor/size + steps*0.0356/size +0.05*conflictos/size+0.12*fails;
}

State::~State() {
  // Se elimina el tablero del State
  int size = 0;
  for (int i = 0; i < this->size; i++) {
    delete[] board[i];
  }
  delete[] board;
}

void State::print_board() {
  // Se imprime elemento por elemento el tablero del State
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

void State::print() {
  // Se imprime de manera recursiva el camino que llevo a la solucion
  // Si el padre no es nulo
  if (parent != nullptr) {
    // Se sigue buscando el padre del estado inicial
    parent->print();
  }

  // Si se encuentra, se imprime su tablero
  print_board();
  cout << endl;
}

bool State::isSol() {
  // Se verifica elemento a elemento si el tablero actual es solucion
  int k = 1;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (this->board[i][j] != (k % (size * size))) {
        return false;
      }
      k++;
    }
  }
  return true;
}

State *State::copy() {
  // Se genera una copia del State
  State *new_state = new State(size, this);
  new_state->board = new int *[size];
  for (int i = 0; i < size; i++) {
    new_state->board[i] = new int[size];
    for (int j = 0; j < size; j++) {
      new_state->board[i][j] = board[i][j];
    }
  }
  new_state->i0 = i0;
  new_state->j0 = j0;
  new_state->steps = steps;
  return new_state;
}

State *State::up() {
  // Si el 0 no esta en la primera fila
  if (i0 != 0) {
    // Se copia el State
    State *new_state = copy();
    // Se mueve el 0
    new_state->board[i0][j0] = board[i0 - 1][j0];
    new_state->board[i0 - 1][j0] = 0;
    // Se actualiza su posicion en i y su heuristica
    new_state->i0--;
    new_state->steps++;
    //Se crea el id del nuevo estado y se actualiza su heuristica
    new_state->createId();
    new_state->act_value();
    return new_state;
  }
  return (nullptr);
}

State *State::down() {
  // Si el 0 no esta en la ultima fila
  if (i0 != size - 1) {
    // Se copia el State
    State *new_state = copy();
    // Se mueve el 0
    new_state->board[i0][j0] = board[i0 + 1][j0];
    new_state->board[i0 + 1][j0] = 0;
    // Se actualiza el valor de su posicion i y la heuristica
    new_state->i0++;
    new_state->steps++;
    //Se crea el id del nuevo estado y se actualiza su heuristica
    new_state->createId();
    new_state->act_value();
    return new_state;
  }
  return (nullptr);
}

State *State::right() {
  // Si el 0 no esta en la ultima columna
  if (j0 != size - 1) {
    // Se copia el State
    State *new_state = copy();
    // Se mueve el 0
    new_state->board[i0][j0] = board[i0][j0 + 1];
    new_state->board[i0][j0 + 1] = 0;
    // Se actualiza su posicion j y la heuristica
    new_state->j0++;
    new_state->steps++;
    //Se crea el id del nuevo estado y se actualiza su heuristica
    new_state->createId();
    new_state->act_value();
    return new_state;
  }
  return (nullptr);
}

State *State::left() {
  // Si el 0 no esta en la primera columna
  if (j0 != 0) {
    // Se copia el State
    State *new_state = copy();
    // Se mueve el 0
    new_state->board[i0][j0] = board[i0][j0 - 1];
    new_state->board[i0][j0 - 1] = 0;
    // Se actualiza su posicion j y la heuristica
    new_state->j0--;
    new_state->steps++;
    //Se crea el id del nuevo estado y se actualiza su heuristica
    new_state->createId();
    new_state->act_value();
    return new_state;
  }
  return (nullptr);
}

bool State::equals(State *s) {
  // Se comparan los tableros elemento a elemento
  if (this->id != s->id) {
    return false;
  }
  for (int i = 0; i < this->size; i++) {
    for (int j = 0; j < this->size; j++) {
      if (this->board[i][j] != s->board[i][j]) {
        // Si se encuentra un error se retorna false
        return false;
      }
    }
  }
  // Sino se retorna true
  return true;
}
