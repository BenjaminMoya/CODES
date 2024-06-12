#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <limits>
#include "TH.h"

class Puzzle {

    public:

        DLL *check; //Lista que guarda los estados ya revisados
        TH *generates; //Tabla hash que guarda los estados generados no revisados
        //Metodos
        Puzzle();
        void generateInitial(State *s);
        State *read();
        //Heuristicas
        double manhattan(State *s);
        State *findBest(DLL *l);
        void solveNoHeuristic();
        void solveHeuristic();
        //Menu
        void menu();

};