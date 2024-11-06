#include "Cargar_tablero.h"
#include "Puzzle.h"
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

int main() {
  // Se declaran variables para uso general
  int option = 0;
  time_t start, end;
  Puzzle *puzzle;
  // Mientras option no sea 2 se sigue iterando
  while (option != 2) {
    // Se declaran e inicializan variables de posicion y tamanio
    string filename;
    int n;
    int **board;
    Cargar_tablero *tablero;
    //  Se pide al usuario ingresar una opcion
    cout << "Solucion de puzzles con algoritmo A*" << endl;
    cout << "Ingrese la accion desea realizar:" << endl;
    cout << "1) Resolver un Puzzle" << endl;
    cout << "2) Salir" << endl;
    cout << "Ingrese opcion: ";
    cin >> option;
    switch (option) {
    case 1:
      // Se pide al usuario ingresar el nombre del archivo
      cout << "Nombre de archivo: ";
      cin >> filename;
      cout << "Leyendo archivo " << filename << endl;
      tablero = new Cargar_tablero(filename);
      board = tablero->Obtener_tablero();
      n = tablero->tamanio();
      // Se obtiene el tiempo de inicio
      start = clock();
      // Se genera un puzzle
      puzzle = new Puzzle(board, n);
      // Se busca la solucion
      puzzle->solve();
      // Se obtiene el tiempo de finalizacion
      end = clock();
      // Se calcula y muestra el tiempo que demoro en solucionarse el puzzle
      cout << "tiempo: " << (end - start) / CLOCKS_PER_SEC << " segundos" << endl;
      cout << endl;
      break;

    case 2:
      // Se imprime un mensaje de salida
      cout << "Saliendo..." << endl;
      break;
    }
  }
  // Se termina el programa luego de salir del ciclo
  return 0;
}
