#include <iostream>
#include "State.h"

State::State(){ //Constructor vacio

    board = nullptr; 
    size = 0 ;
    parent = nullptr;
    i0 = -1;
    j0 = -1;

}

State::State(int size) { //Constructor con tamano por defecto

    this->size = size;
    this->board = new int*[size];

    for(int i=0; i<size; i++) { //Rellena el tablero con 0 para inicializarlo

        this->board[i] = new int[size];

        for(int j=0; j<size; j++) {

            this->board[i][j] = 0;

        }

    }

    this->parent = nullptr;
    i0 = -1;
    j0 = -1;

}

State::State(int size, State *parent) { //Constructor con tamano y antecesor por defecto

    this->size = size;
    this->board = new int*[size];

    for(int i=0; i<size; i++) { //Rellena el tablero con 0 para inicializarlo

        this->board[i] = new int[size];

        for(int j=0; j<size; j++) {

            this->board[i][j] = 0;

        }

    }

    this->parent = parent; //Asigna el parametro parent como su antecesor
    i0 = -1;
    j0 = -1;

}

State::State(int size, State *parent, int **board) { //Constructor con tamano, antecesor y tablero por defecto

    this->size = size;
    this->board = new int*[size];

    for(int i=0; i<size; i++) { //Inicializa el tablero con los valores del tablero en parametro

        this->board[i] = new int[size];

        for(int j=0; j<size; j++) {

            this->board[i][j] = board[i][j];

        }
    }

    this->parent = parent; //Asigna el parametro parent como su antecesor
    i0 = -1;
    j0 = -1;

}

void State::print(){ //Imprime el tablero

    
    for (int i=0;i<size;i++){

        for (int j=0;j<size;j++){

            std::cout << board[i][j] << " ";
            
        }

        std::cout << std::endl;

    }

}

void State::printParents(){ //Funcion recursiva que imprime los tableros desde el origen hasta en el actual

    if(parent != nullptr){

        parent->printParents();

    }

    print();
    std::cout << std::endl;

}

State *State::copy(){ //Copia el estado y retorna uno nuevo

    State *newState = new State(size, this);
    newState->board = new int*[size];

    for(int i=0; i<size; i++) {

        newState->board[i] = new int[size];

        for(int j=0; j<size; j++) {

            newState->board[i][j] = board[i][j];

        }
    }

    newState->i0 = i0;
    newState->j0 = j0;
    return newState;
    
}

State *State::up(){ //Mueve el vacio hacia arriba

    if(i0!=0){ //Si el vacio esta en la fila superior no se realiza el movimiento

        State *newState = copy();
        newState->board[i0][j0] = board[i0-1][j0];
        newState->board[i0-1][j0] = 0;
        newState->i0--;
        return newState;

    }

    return nullptr;

}

State *State::down(){ //Mueve el vacio hacia abajo

    if(i0!=size-1){ //Si el vacio esta en la fila inferior no se realiza el movimiento

        State *newState = copy();
        newState->board[i0][j0] = board[i0+1][j0];
        newState->board[i0+1][j0] = 0;
        newState->i0++;
        return newState;

    }

    return nullptr;
    
}

State *State::right(){ //Mueve el vacio hacia la derecha

    if(j0!=size-1){ //Si el vacio estta en la orilla derecha no se realiza el movimiento

        State *newState = copy();
        newState->board[i0][j0] = board[i0][j0+1];
        newState->board[i0][j0+1] = 0;
        newState->j0++;
        return newState;

    }

    return nullptr;
    
}

State *State::left(){ //Mueve el vacio hacia la izquierda

    if(j0!=0){ //Si el vacio esta en la orilla izquierda no se realiza el movimiento

        State *newState = copy();
        newState->board[i0][j0] = board[i0][j0-1];
        newState->board[i0][j0-1] = 0;
        newState->j0--;
        return newState;

    }

    return nullptr;
    
}

bool State::eq(State *s){ //Compara dos estados y verifica si son iguales atraves de su tablero asociado

    
    for(int i=0; i<this->size; i++) {

        for(int j=0; j<this->size; j++) {

            if (this->board[i][j] != s->board[i][j]) {

                return false;

            }

        }

    } 

    return true;

}

bool State::isSolution(){ //Verifica si el estado es solucion

    int k=1;

    for(int i=0; i<size; i++) {

        for(int j=0; j<size; j++) {

            if (board[i][j] != (k%(size*size)))  {

                return false;

            }

            k++;

        }

    }

    return true; 

}

double State::manhattan(){ //Calcula y retorna el coeficiente Manhattan asociado al tablero
    
    int coef = 0;
    int n = size;

    for (int i = 0; i < n; ++i) {

        for (int j = 0; j < n; ++j) {

            if (board[i][j] != 0) {

                int row = (board[i][j] - 1) / n;
                int col = (board[i][j] - 1) % n;
                coef += abs(i - row) + abs(j - col);

            }

        }

    }

    return coef;

}

State::~State() {  //Destructor de la clase

    int size=0;

    for(int i=0; i<size; i++) {

        delete [] board[i];

    }

    delete [] board;

}