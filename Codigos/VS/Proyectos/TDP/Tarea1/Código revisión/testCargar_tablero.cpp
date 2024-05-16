#include "Cargar_tablero.h"
int main() {
  // Se carga el tablero2.txt
  Cargar_tablero *c = new Cargar_tablero("tablero2.txt");
  // Se obtienen el tablero y el tamaño, para luego imprimirse
  int **tablero = c->Obtener_tablero();
  int size = c->tamanio();
  cout << "El tamaño del tablero es: " << size << endl;
}