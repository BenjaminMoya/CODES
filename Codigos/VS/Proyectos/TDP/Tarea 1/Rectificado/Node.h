#include <iostream>
#include "State.h"

class Node{ //Clase contenedora de estados con tal de facilitar su manejo mediante listas

    public:

        State *data; //Estado asociado
        Node *next; //Nodo siguiente
        Node *prev; //Nodo anterior
        //Metodos
        Node();
        Node(State *s);
        bool eq(Node *n);
        ~Node();

};