#include <iostream>
#include "Node.h"

Node::Node(){ //Constructor vacio

    data = nullptr;
    next = nullptr;
    prev = nullptr;

}

Node::Node(State *s){ //Constuctor con clase por defecto

    data = s;
    next = nullptr;
    prev = nullptr;

}

bool Node::eq(Node *n){ //Compara si 2 nodos son iguales segun sus estados

    if((data)->eq(n->data)){

        return true;
    }

    return false;
    
}

Node::~Node(){ //Destructor

    
}