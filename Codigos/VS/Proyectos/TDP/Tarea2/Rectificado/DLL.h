#include <iostream>
#include <limits>
#include "Node.h"
using namespace std;

class DLL{ //Lista doblemente enlazada que funciona como contenedora de los nodos con estados

    public:
         
        int size; //Tamano de la lista
        Node *head; //Cabeza de la lista
        Node *tail; //Cola de la lista
        //Metodos
        DLL();
        DLL(int info);
        bool isEmpty();
        void insertFront(int info);
        void insertBack(int info);
        int *removeFront();
        int *removeBack();
        bool find(int info);
        void remove(int info);
        void display();
        ~DLL();


};