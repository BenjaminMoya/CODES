#include <iostream>
using namespace std;

class Node{ //Clase contenedora de estados con tal de facilitar su manejo mediante listas

    public:

        int *data; //Estado asociado
        Node *next; //Nodo siguiente
        Node *prev; //Nodo anterior
        //Metodos
        Node();
        Node(int info);
        bool eq(Node *n);
        ~Node();

};