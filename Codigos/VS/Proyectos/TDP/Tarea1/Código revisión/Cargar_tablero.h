#include <iostream>
#include <string>
using namespace std;

class Cargar_tablero {
public:
  int **board;
  int size;
  Cargar_tablero(string filename);
  ~Cargar_tablero();
  int tamanio();
  int **Obtener_tablero();
};