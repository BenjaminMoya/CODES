#include <iostream>
#include "Node.h"

Node::Node(){ //Constructor vacio

    data = nullptr;
    next = nullptr;
    prev = nullptr;

}

Node::Node(int info){ //Constuctor con clase por defecto

    data = new int (info);
    next = nullptr;
    prev = nullptr;

}

bool Node::eq(Node *n){ //Compara si 2 nodos son iguales segun sus estados

    if(data==(n->data)){

        return true;
    }

    return false;
    
}

Node::~Node(){ //Destructor

    
}