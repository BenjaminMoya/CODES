#include <iostream>
#include "DLL.h"

DLL::DLL(){ //Constructor vacio

    size = 0;
    head = nullptr;
    tail = nullptr;

}

DLL::DLL(int info){ //Constructor con estatdo por defecto como primer elemento

    Node *newNode = new Node(info);
    size++;
    head = tail = newNode;

}

bool DLL::isEmpty(){ //Verifica si la lista esta vacia

    if(size==0){

        return true;
        
    }

    return false;

}

void DLL::insertFront(int info){ //Inserta un nodo al comienzo de la lista
    
    Node *newNode = new Node(info);

    if (isEmpty()){ //Si la lista esta vacia el nodo corresponde al primer elemento 

        head = tail = newNode;
        size++;
        return;

    } else { //Sino se conecta con el head anterior y el nuevo nodo pasa a ser el actual head

        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        size++;
        return;
        
    }

}

void DLL::insertBack(int info){ //Inserta un nodo al final de la lista

    Node *newNode = new Node(info);

    if(isEmpty()){ //Si la lista esta vacia el nodo corresponde al primer elemento

        head = tail = newNode;
        size++;
        return;

    } else { //Sino se conecta con el tail anterior y el nuevo nodo pasa a ser el actual tail

        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        size++;
        return;
        
    }

}

int *DLL::removeFront(){ //Remueve y retorna el nodo al comienzo de la lista

    if(isEmpty()){ //Si la lista esta vacia no retorna nada

        return nullptr;

    } else if(size==1){ //Si la lista tiene un elemento remueve el nodo inicial y lo retorna

        Node *temp = head;
        head = nullptr;
        size--;
        return temp->data;

    } else { //Si la lista tiene mas elementos, el elemento siguiente al head pasa a ser el head actual y su puntero al nodo anterior apuntara a nulo

        Node *temp = head;
        head = head->next;
        head->prev = nullptr;
        size--;
        return temp->data;

    }

}

int *DLL::removeBack(){ //Remueve y retorna el nodo al final de la lista

    if(isEmpty()){ //Si la lista esta vacia no retorna nada

        return nullptr;

    } else if(size==1){ //Si la lista tiene un elemento remueve el nodo final y lo retorna

        Node *temp = tail;
        tail = nullptr;
        size--;
        return temp->data;

    } else { //Si la lista tiene mas elementos, el elemento anterior al tail pasa a ser el tail actual y su puntero al nodo siguiente apuntara a nulo

        Node *temp = tail;
        tail = tail->prev;
        tail->next = nullptr;
        size--;
        return temp->data;

    }

}

bool DLL::find(int info){ //Verifica si un nodo esta en la lista segun su estado
    
    if(isEmpty()){ //Si la lista esta vacia, no se encontro
        
        return false;

    }

    Node *left = head;
    Node *rigth = tail;
    
    while(left != nullptr && rigth != nullptr){ //Se busca por ambos extremos para acortar la busqueda, donde si uno de los punteros queda nulo es porque no se ha encontrado el elemento

        if(*(left->data)==info){ 
    
            return true;

        }

        if(*(rigth->data)==info){

            return true;

        }
        
        left = left->next;
        rigth = rigth->prev;
        
    }
    
    return false;

}

void DLL::remove(int info){ //Remueve un nodo en especifico de la lista
    
    if(isEmpty()){ //Si la lista esta vacia no no se hace nada
        
        return;

    }

    Node *left = head;
    Node *rigth = tail; //Se busca por ambos extremos para acortar la busqueda
    int *aux; //Auxiliar asignado para confirmar que se ha removido el nodo con exito

    while(left != nullptr && rigth != nullptr){ //Si uno de los punteros queda nulo es porque no se ha encontrado el elemento
        
        if(*(left->data)==info){ //El puntero izquierdo lo encontro
            
            if(size == 1){ //Si la lista tiene un elemento se deja todo en nulo

                head = nullptr;
                tail = nullptr;
                size--;
                return;

            }    
            if(left->prev == nullptr){ //Si la lista tiene mas elementos y se encontro en el head, se invoca la funcion que remueve el primer elemento

                aux = removeFront();
                return;

            } else { //Si la lista tiene mas elementos y esta entremedio el que vamos a quitar, asignamos sus nodos adyacente entre ellos eliminando su relacion con el a remover

                (left->prev)->next = left->next;
                (left->next)->prev = left->prev;
                size--;
                return;

            }

        }
        
        if(*(rigth->data)==info){ //El puntero derecho lo encontro

            if(size == 1){ //Si la lista tiene un elemento se deja todo en nulo

                head = nullptr;
                tail = nullptr;
                size--;
                return;
            }    
            if(rigth->next == nullptr){ //Si la lista tiene mas elementos y se encontro en el tail, se invoca la funcion que remueve el ultimo elemento

                aux = removeBack();
                return;
                
            } else { //Si la lista tiene mas elementos y esta entremedio el que vamos a quitar, asignamos sus nodos adyacente entre ellos eliminando su relacion con el a remover

                (rigth->prev)->next = rigth->next;
                (rigth->next)->prev = rigth->prev; 
                size--;
                return;

            }

        }
        
        left = left->next;
        rigth = rigth->prev;
        
    }
    
    return;

}

void DLL::display(){ //Imprime la lista por consola

    if (isEmpty()){ //Si estat vacia imprime un -1

        cout << "-1" << endl;
        return;


    } else { //Sino la recorre imprimiendo el tablero de cada estado asociado al nodo correspondiente

        Node *temp = head;

        while(temp!=nullptr){

            cout << (temp->data);
            temp = temp->next;
        }

        return;

    }

}

DLL::~DLL(){ //Desttrcutor de la clase

    while(size!=1){

        removeFront();
        
    }

    Node *temp = head;
    head = nullptr;
    delete head;
    
}