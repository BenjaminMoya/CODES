#include "Puzzle.h"
using namespace std;
int main() {
  // Se crea un tablero de tamaño 3
  int size = 3;
  int **board = new int *[size];
  for (int i = 0; i < size; i++) {
    board[i] = new int[size];
  }
  board[0][0] = 1;
  board[0][1] = 2;
  board[0][2] = 3;
  board[1][0] = 4;
  board[1][1] = 0;
  board[1][2] = 5;
  board[2][0] = 7;
  board[2][1] = 8;
  board[2][2] = 6;
  // Se crea el puzzle
  Puzzle *p = new Puzzle(board, size);
  // Se resuelve el puzzle
  p->solve();
  return 0;
}