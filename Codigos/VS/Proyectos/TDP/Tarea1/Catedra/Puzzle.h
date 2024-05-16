#include <iostream>
#include "Stack.h"

class Puzzle {

    public: 

        int **board;  // Matriz que representa el puzzle original
        int size;
        Stack *open; // Repositorio de estados por visitar
        Stack *all; // Repositorio de de todos los estados que ya fueron generados 
        Puzzle();
        Puzzle(char * filename); // Carga desde un archivo extetrno el tablero inicial
        ~Puzzle();
        State * generate_init(); // Genera el estado inicial desde board
        void solve(); // Opera el algoritmo A*

};