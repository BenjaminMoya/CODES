#include "Puzzle.h"

Puzzle::Puzzle() {

    size = 0;
    board = nullptr;
    open = new Stack(100);
    all = new Stack(100);

}

State * Puzzle::generate_init() { // Asumiendo que board ya esta cargado
    
    State *e = new State(size, nullptr, board);
    e -> parent=nullptr;
    e -> i0 = -1; 
    e -> j0 = -1;

    if (board==nullptr) {

        std::cout << "No se ha cargado el tablero" << std::endl;
        return nullptr;

    }

    // En caso de no encontrar el cero se busca

    for (int i=0; i<size; i++) {

        for (int j=0; j<size; j++) {

            if (board[i][j]==0) {

                e -> i0 = i;
                e -> j0 = j;
                return e;

            }

        }

    }

    return e;

}

void Puzzle::solve() {

    State *e_init = generate_init(); // Genera el estado inicial

    if (e_init==nullptr) { // Si falla la generacion se retorna nulo

        std::cout << "No se pudo generar el estado inicial" << std::endl;
        return;

    }

    open -> push(e_init); // Agrega en los abierto y cerrados el tablero inicial para marca su comienzo y generacion
    all -> push(e_init); 

    while (!open->isEmpty()) { // Mientras existan nodos por visitar

        State *e = open -> pop(); 
        std::cout << "Estado actual:"<< e << " i0:" << e->i0 << " j0:" << e->j0 << " size:" << e->size << " parent:"<< e->parent << std::endl;

        if (e->isSolution()) {

            std::cout << "Encontramos la solucion:" << std::endl;
            e -> print();
            return;

        }

        // Expandir el estado e -> notar la repeticion que se hace (no es buena practica, deberia disponerse de un arreglo de movimientos posibles)
        
        State *e_up = e -> up();  // Si genera estado invalido, genera nullptr

        if (e_up!=nullptr && !all->find(e_up)) { // Si es valido y si no esta en todos

            open -> push(e_up);
            all -> push(e_up);

        }

        State *e_down = e -> down();  // Si genera estado invalido, genera nullptr

        if (e_down!=nullptr && !all->find(e_down)) {

            open -> push(e_down);
            all -> push(e_down);

        }

        State *e_left = e -> left();  // Si genera estado invalido, genera nullptr

        if (e_left!=nullptr && !all->find(e_left)) {

            open -> push(e_left);
            all -> push(e_left);

        }

        State *e_right = e->right();  // Si genera estado invalido, genera nullptr

        if (e_right!=nullptr && !all->find(e_right)) {

            open -> push(e_right);
            all -> push(e_right);

        }

    }

    std::cout<< "No se encontro solucion" << std::endl;

}