#include <iostream>
#include "State.h"

int main(){

    State *s1 = new State(2);
    State *s2 = new State(2);
    State *s3 = new State(2,s2);
    s1->board[0][0] = 1;
    s1->board[0][1] = 2;
    s1->board[1][0] = 3;
    s1->board[1][1] = 0;
    s2->parent = s1;
    State *s4 = new State(2,s3,s1->board);
    std::cout << "Primera generacion de estados: " << std::endl;
    std::cout << std::endl;
    s4->printParents();
    s4->i0 = 1;
    s4->j0 = 1;
    State *s5 = s4->up();
    std::cout << "Segunda generacion con movimientos de vacio: " << std::endl;
    std::cout << std::endl;
    s5->printParents();
    State *s6 = s5->down();
    std::cout << "Verificacion de estado solucion: " << std::endl;
    std::cout << std::endl;
    std::cout << "Estado 1:";
    std::cout << s1->isSolution() << std::endl;
    std::cout << "Estado 6:";
    std::cout << s6->isSolution() << std::endl;
    std::cout << std::endl;
    std::cout << "Generacion de coeficiente Manhattan" << std::endl;
    std::cout << s6->manhattan() << std::endl;
    return 0;

}