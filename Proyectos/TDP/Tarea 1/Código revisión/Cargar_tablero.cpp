#include "Cargar_tablero.h"
#include <fstream>
#include <sstream>

Cargar_tablero::Cargar_tablero(string filename) {
  int num, n = 0;
  string line;
  stringstream ss;
  ifstream file;
  file.open(filename);
  // Se verifica si se pudo abrir el archivo
  if (!file.is_open()) {
    cout << "No se pudo abrir el archivo" << endl;
    exit(-1);
  }

  // Se obtiene el tamaño del tablero
  if (getline(file, line, '\n')) {
    ss << line;
    while (ss >> num) {
      n++;
    }
  }
  // Se cierra el archivo
  file.close();
  // Se inicializa el tablero con el tamaño obtenido
  board = new int *[n];
  for (int i = 0; i < n; i++) {
    board[i] = new int[n];
  }
  // Se abre el archivo
  file.open(filename);
  // Se llena el tablero con los datos del archivo
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      file >> board[i][j];
    }
  }
  file.close();

  // Se imprime el tablero leido
  cout << "Se leyo el tablero correctamente:" << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
  size = n;
}

Cargar_tablero::~Cargar_tablero() {
  for (int i = 0; i < size; i++) {
    delete[] board[i];
  }
  delete[] board;
}

int Cargar_tablero::tamanio() { return size; }

int **Cargar_tablero::Obtener_tablero() { return board; }