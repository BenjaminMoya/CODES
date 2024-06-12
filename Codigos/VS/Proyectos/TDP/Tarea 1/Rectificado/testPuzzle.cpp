#include <iostream>
#include "Puzzle.h"

int main(){ //No se revisara el metodo menu, ni los de resolucion para no probar individualmente funcionalidades que no son tan vistas 

    Puzzle *p =  new Puzzle();
    State *s = p->read();
    std::cout << "Tablero leido: " << std::endl;
    s->print();
    p->generateInitial(s);
    std::cout << "Estado inicial generado como primer elemento de la primera lista solo si contiene el 0 " << std::endl;
    p->generates->sets[0]->display();
    return 0;
    
}