#include "State.h"

State::State(){

    board=nullptr; 
    size=0;
    parent=nullptr;

}

State::State(int size) {

    this->size = size;
    this->board = new int*[size];

    for(int i=0; i<size; i++) {

        this->board[i] = new int[size];

        for(int j=0; j<size; j++) {

            this->board[i][j] = 0;

        }

    }

    this->parent = nullptr;

}

State::State(int size, State *parent) {

    this->size = size;
    this->board = new int*[size];

    for(int i=0; i<size; i++) {

        this->board[i] = new int[size];

        for(int j=0; j<size; j++) {

            this->board[i][j] = 0;

        }

    }

    this->parent = parent;

}

State::State(int size, State *parent, int **board) {

    this->size = size;
    this->board = new int*[size];

    for(int i=0; i<size; i++) {

        this->board[i] = new int[size];

        for(int j=0; j<size; j++) {

            //std::cout << "i=" << i << " j=" << j << " board[i][j]=" << board[i][j] << std::endl;
            this->board[i][j] = board[i][j];
        }
    }

    this->parent = parent;

}

State::~State() {

    int size=0;

    for(int i=0; i<this->size; i++) {

        delete [] board[i];

    }

    delete [] board;

}

void State::print_board() {

    for(int i=0; i<size; i++) {

        for(int j=0; j<size; j++) {

            std::cout << board[i][j] << " ";
            
        }

        std::cout << std::endl;

    }

}

void State::print() {

    if (parent != nullptr) {

       parent->print();

    } 
    
    print_board();
    std::cout << std::endl;

}

bool State::isSolution() {

    int k=1;

    for(int i=0; i<size; i++) {

        for(int j=0; j<size; j++) {

            if (this->board[i][j] != (k%(size*size)))  {

                return false;

            }

            k++;

        }

    }

    return true; 

}

State* State::copy() {

    State *new_state = new State(size, this);
    new_state->board = new int*[size];

    for(int i=0; i<size; i++) {

        new_state->board[i] = new int[size];

        for(int j=0; j<size; j++) {

            new_state->board[i][j] = board[i][j];

        }
    }

    new_state->i0 = i0;
    new_state->j0 = j0;
    return new_state;

}

State * State::up() {

    if (i0!=0) {  // Si no esta en la primera fila entonces puedo subir el 0

        State *new_state = copy();
        new_state->board[i0][j0]=board[i0-1][j0];
        new_state->board[i0-1][j0]=0;
        new_state->i0--;
        return new_state;

    }

    return(nullptr);

}

State * State::down() {

    if (i0!=size-1) {  // Si no esta en la ultima fila entonces puedo bajar el 0

        State *new_state = copy();
        new_state->board[i0][j0]=board[i0+1][j0];
        new_state->board[i0+1][j0]=0;
        new_state->i0++;
        return new_state;

    }

    return(nullptr);

}

State * State::right() {

    if (j0!=size-1) { // Si no esta en la ultima columna entonces puedo mover el 0 hacia la derecha

        State *new_state = copy();
        new_state->board[i0][j0]=board[i0][j0+1];
        new_state->board[i0][j0+1]=0;
        new_state->j0++;
        return new_state;

    }

    return(nullptr);

}

State * State::left() {

    if (j0!=0) { // Si no esta en la primera columna entonces puedo mover el 0 hacia la izquierda

        State *new_state = copy();
        new_state->board[i0][j0]=board[i0][j0-1];
        new_state->board[i0][j0-1]=0;
        new_state->j0--;
        return new_state;

    }

    return(nullptr);

}

bool State::equals(State *s) { // Comparamos solo el atributo tablero ya que el resto deberian ser los mismos a menos de que exista un error de implementacion

    for(int i=0; i<this->size; i++) {

        for(int j=0; j<this->size; j++) {

            if (this->board[i][j] != s->board[i][j]) {

                return false;

            }

        }

    } 

    return true;

}