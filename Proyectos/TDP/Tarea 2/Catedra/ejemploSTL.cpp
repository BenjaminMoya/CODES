#include <iostream>
#include <set>
#include "State.h"

using namespace std;


int main() {
    // Functor
    struct functor {
        int i;
        int f(int x) {
            i=x;
            return x;
        }
    };
    functor variable_f;
    int x=variable_f.f(5);
    cout << "Prueba de functores:"<< endl;
    std::cout << variable_f.i << std::endl; 

    cout<< "Prueba de de iteraddores en set"<< endl;
    // oficalmente el manual de c++ esta en 
    // https://en.cppreference.com/   
    set<int> conjunto_entero;

    conjunto_entero.insert(5);
    conjunto_entero.insert(1);
    conjunto_entero.insert(6);
    conjunto_entero.insert(2);
    // begin() retorna un iterador al inicio del contenedor
    // end es un iterador que esta  despues del ultimo elemento
    for (auto it = conjunto_entero.begin(); it != conjunto_entero.end(); it++) {
        // it++ : pasar al siguiente elemento
        std::cout << *it << std::endl; // *it: acceder al valor del iterador
    }

    cout << "Prueba con set de State*"<< endl;
    struct comp {
        //public:
            bool operator()(State *a, State *b) const {
                // mientras son iguales los tableros avanzo hasta encontrar celda distinta que comparo
                int i=0, j=0;
                while(a->board[i][j] == b->board[i][j]) {
                    j++;
                    if(j == a->size) {
                        j = 0;
                        i++;
                    }
                    if(i == a->size) {
                        return false; // son iguales los tableros
                    }
                }
                // llegue a una celda distinta
                return a->board[i][j] < b->board[i][j];
            }
    };

    set<State*,comp> c; // c es un contenedor de punteros a estado ordenados
    int n=3; 
    int **board=new int*[n];
    for (int i=0; i<n; i++) {
        board[i] = new int[n];
        for (int j=0; j<n; j++) {
            board[i][j] = n*i+j+1;
        }
    }

    board[n-1][n-1]=0;
    State *s1 = new State(n,nullptr,board);
    s1->i0=n-1;
    s1->j0=n-1;

    State *s2 = s1->up();
    State *s3 = s2->up();
    State *s4 = s3->left();

    c.insert(s1);
    c.insert(s2);
    c.insert(s3);
    c.insert(s4);

    for (auto it = c.begin(); it != c.end(); it++) {
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                cout << (*it)->board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    State *s5= s4->left();

    auto it = c.find(s5);
    if (it == c.end()) { // si es que este iterador esta fuera del conjunto (end)
        cout << "No esta en el conjunto" << endl;
    } else {
        cout << "Esta en el conjunto" << endl;
    }

    auto it2 = c.find(s3);
    if (it2 == c.end()) { // si es que este iterador esta fuera del conjunto (end)
        cout << "No esta en el conjunto" << endl;
    } else {
        cout << "Esta en el conjunto" << endl;
    }

    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout << (*it2)->board[i][j] << " ";
        }

        cout << endl;
    }
    cout<<endl;


    return 0;


}