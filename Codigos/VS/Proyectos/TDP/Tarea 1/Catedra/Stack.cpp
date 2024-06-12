#include "Stack.h"

Stack::Stack(){ 

    size=100; // Por defecto construye stack de tamaño 100
    data = new State*[size];

}

Stack::Stack(int n) {

    data = new State*[n]; // Crea memoria para objeto int en arreglo de tamaño n
    size=n;
    top=-1;

}

Stack::~Stack() {
    
    delete[] data; 
    
}

bool Stack::isEmpty() {

    return (top==-1); 
   
}

void Stack::push(State * s) {

    if (top==size-1) {

        State **data_tmp = new State*[size*2];// Si el stack esta lleno crea un nuevo arreglo del doble del tamaño original y copia los elementos

        for (int i=0; i<size; i++) {

            data_tmp[i]=data[i]; 

        }

        delete[] data; 
        data=data_tmp; // Asigna el nuevo puntero a data
        size*=2; // Actualiza el tamaño 

    }

    ++top;
    data[top]=s; // Incrementa top y luego asigna s

} 

State * Stack::pop() {

    if (isEmpty()) {

        std::cout << "Stack Underflow" << std::endl;
        return nullptr; // Si no hay elementos para eliminar, retorna nulo

    }

    return (data[top--]); // Devuelve el puntero y decrementa top

}

bool Stack::find(State * e) {

    for (int i=0; i<=top; i++) {

        if (data[i]->equals(e)) {

            return true;

        }

    }

    return false;

}
