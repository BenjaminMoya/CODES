#include <iostream>
#include "Puzzle.h"

int main(){ //Funcion principal del programa

    Puzzle *p = new Puzzle();  //Inicializa un objeto tipo puzzle
    p->menu(); //Inicia la interaccion con el usuario
    return 0;
}