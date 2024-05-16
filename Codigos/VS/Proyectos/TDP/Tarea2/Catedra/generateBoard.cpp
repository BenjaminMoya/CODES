#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
#include "State.h"
#include <time.h>
using namespace std;

int main() {
    int n;
    string name;
    int **board;
    srand(time(NULL));

    cout << "Ingrese el tamaño del tablero: ";
    cin >> n;
    board = new int*[n];
    for (int i = 0; i < n; i++) {
        board[i] = new int[n];
    }

    cout << "Ingrese nombre de salida: ";
    cin >> name;

    cout << "Ingrese cantidad de pasos random: " << endl;
    int steps;
    cin >> steps;

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            board[i][j] = i*n+j+1;
        }
    }

    board[n-1][n-1] = 0;

    // esto es un functor para comparar dos estados
    // se usa para el set pueda ordenar los estados y compararlos con <
    // en orden lexicografico
    struct comp {
        bool operator()(const State* lhs, const State* rhs) const {
            int i=0,j=0;
            // buscar la primera casilla distinta
            while(lhs->board[i][j] == rhs->board[i][j]) {
                j++;
                if(j == lhs->size) {
                    j = 0;
                    i++;
                }
                if(i == lhs->size) {
                    return false;
                }
            } // si llego aca, encontro una casilla distinta, entonces esta es la que define el orden
            return lhs->board[i][j] < rhs->board[i][j];
        }
    };

    set<State *,comp> visited;
    State *initial = new State(n, nullptr, board);
    initial->print();
    initial->i0=n-1;
    initial->j0=n-1;
    visited.insert(initial);
    State *current = initial;
    State *next = nullptr; 
    while (steps > 0) { // mala practica : debiese ser arreglo de operadores
        int op = rand() % 4;
        switch (op) {
          case 0:
            next = current->up();
            cout << "up" << endl;
            break;
          case 1:
            next = current->down();
            cout << "down" << endl;
            break;
          case 2:
            next = current->left();
            cout << "left" << endl;
            break;
          case 3:
            next = current->right();
            cout << "right" << endl;
            break;
        }
        if (next != nullptr  // si se puede mover
            && visited.find(next) == visited.end()) { // y no se ha visitado
            visited.insert(next);
            next->print();
            current = next;
            cout<< "step "<<steps<<endl;
            steps--;
        } else {
          if (next != nullptr) {
            delete next;
            cout << "ya existe en el conjunto" << endl;
          } else {
            cout << "no se puede mover" << endl;
          }

        }
    } // termino con un tablero aleatorio en current

    // escribir tablero en archivo
    ofstream file(name+"_"+to_string(n)+"_"+to_string(steps)+".txt");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n-1; j++) {
            file << current->board[i][j] << " ";
        }
        file << current->board[i][n-1] << endl;
    }
    file.close();
}