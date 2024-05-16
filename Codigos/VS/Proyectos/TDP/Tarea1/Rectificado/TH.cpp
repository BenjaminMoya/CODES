#include <iostream>
#include "TH.h"

TH::TH(){ //Constructor vacio

    for (int i = 0; i < size; ++i) { //Inicializa una lista por elemento en la tabla

        sets[i] = new DLL();

    }

}

int TH::hashFunction(State *s){ //Funcion hash que retorna el indice de su lista segun su coeficiente Manhattans

    int newNumber = static_cast<int>(s->manhattan());

    if (newNumber<0){

        newNumber = 0;
    }

    if (newNumber>49){

        newNumber = 49;

    }

    return newNumber;
}

void TH::insert(State *s){ //Calcula su coeficiente y lo asocia como su prioridad en la tabla insertandolo en la lista correspondiente
    
    int index = hashFunction(s);
    sets[index]->insertFront(s);
    return;

}

bool TH::isEmpty(){ //Verifica si la tabla esta vacia

    for(int i=0;i<size;i++){

        if(!(sets[i]->isEmpty())){

            return false;
        }

    }

    return true;
    
}

