#include <iostream>
#include "State.h"

class Stack {

    public:

        State **data; // Arreglo de punteros a objetos de la clase State
        int size; 
        int top; // Ultimo elemento del stack. -1 significa que esta vacio
        Stack(int n);
        Stack(); 
        ~Stack();
        bool isEmpty();
        void push(State *s); 
        State * pop();
        bool find(State *e); 

};