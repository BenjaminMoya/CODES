#include <iostream>

class State{//Clase que representa la nocion de estado del algoritmo A* como unidad basica del sistema

    public:

        int **board; //Tablero del estado
        int size; //Tamano del tablero
        int i0; //Posicion fila del vacio
        int j0; //Posicion columna del vacio
        double cost; //Coste de Manhattan acumulado
        State *parent; //Estado anterior
        //Metodos
        State();
        State(int size);
        State(int size, State *parent);
        State(int size, State *parent, int **board);
        void print();
        void printParents();
        State *copy();
        State *up();
        State *down();
        State *left();
        State *right();
        bool eq(State *s);
        bool isSolution();
        double manhattan();
        ~State();


};