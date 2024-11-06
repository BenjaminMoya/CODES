#include "Heap.h"

Heap::Heap(int capacity) {
  // Se inicializan los atributos de la clase
  this->capacity = capacity;
  this->size = 0;
  this->arr = new State *[capacity];
}

Heap::~Heap() {
  // Se libera la memoria de los punteros State dentro del arreglo
  for (int i = 0; i < size; ++i) {
    delete arr[i];
  }
  // Se libera la memoria del arreglo
  delete[] arr;
}

void Heap::push(State *val) {
  // Se verifica si el tamaño del heap es igual a la capacidad
  if (size == capacity) {
    // Se duplica la capacidad del heap
    State **arr_tmp = new State *[capacity * 2];
    // Se copian los elementos del heap original al nuevo heap
    for (int i = 0; i < capacity; i++) {
      arr_tmp[i] = arr[i];
    }
    // Se libera la memoria del heap original
    delete[] arr;
    // Se actualizan los atributos de la clase
    arr = arr_tmp;
    // Se actualiza la capacidad del heap
    capacity *= 2;
  }
  // Se agrega el valor al heap
  arr[size] = val;
  // Se incrementa el tamaño del heap
  size++;
  // Se modifica el heap con heurística
  int i = size - 1;
  // Se ajusta la posición del elemento agregado en el montículo
  int index = size - 1;
  while (index > 0 && (arr[index]->value < arr[(index - 1) / 2]->value)) {
    // Se realiza el swap
    State *temp = arr[index];
    arr[index] = arr[(index - 1) / 2];
    arr[(index - 1) / 2] = temp;
    index = (index - 1) / 2;
  }
}

State *Heap::pop() {
  // Se verifica si el tamaño del heap es igual a 0
  if (size == 0) {
    return nullptr;
  }
  // Se obtiene el primer elemento del heap
  State *val = arr[0];
  // Se actualiza el primer elemento del heap
  arr[0] = arr[size - 1];
  // Se decrementa el tamaño del heap
  size--;
  // Se modifica el heap con heurística
  int i = 0;
  // Se ajusta la posición del primer elemento en el montículo
  while (2 * i + 1 < size) {
    // Se obtienen los hijos izquierdo y derecho
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int min = i;
    // Se verifica si el hijo izquierdo es menor al tamaño del heap
    if (left < size && arr[left]->value < arr[min]->value) {
      // Se actualiza el valor mínimo
      min = left;
    }
    // Se verifica si el hijo derecho es menor al tamaño del heap
    if (right < size && arr[right]->value < arr[min]->value) {
      // Se actualiza el valor mínimo
      min = right;
    }
    // Se verifica si el valor mínimo es igual al valor de i
    if (min == i) {
      // Se rompe el ciclo
      break;
    }
    // Se realiza el swap
    State *temp = arr[i];
    arr[i] = arr[min];
    arr[min] = temp;
    i = min;
  }
  // Se retorna el valor
  return val;
}

bool Heap::isEmpty() {
  // Se verifica si el tamaño del heap es igual a 0
  return size == 0;
}
