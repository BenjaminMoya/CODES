#include <iostream>
#include "DLL.h"

class TH{

    public:

        static const int size = 50; //Cantidad de listas
        DLL *sets[size]; //Tabla hash con la cantidad de listas declaradas
        //Metodos
        TH();
        int hashFunction(State *s);
        void insert(State *s);
        bool isEmpty();

};