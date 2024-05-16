#include <iostream>
#include <limits>
#include "Node.h"

class DLL{ //Lista doblemente enlazada que funciona como contenedora de los nodos con estados

    public:
         
        int size; //Tamano de la lista
        Node *head; //Cabeza de la lista
        Node *tail; //Cola de la lista
        //Metodos
        DLL();
        DLL(State *s);
        bool isEmpty();
        void insertFront(State *s);
        void insertBack(State *s);
        State *removeFront();
        State *removeBack();
        bool find(State *s);
        void remove(State *s);
        void display();
        State *findBest();
        ~DLL();


};