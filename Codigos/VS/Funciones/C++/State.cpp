#include "State.h"
using namespace std;

State::State(){
    size = 0;
    board = nullptr;
    parent = nullptr;
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

void State::print() {
    if (parent != nullptr) {
        parent->print();
    }
    for(int i=0; i<this->size; i++) {
        for(int j=0; j<this->size; j++) {
            std::cout << this->board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

