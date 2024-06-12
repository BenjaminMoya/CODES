#include <iostream>
#include "TH.h"

int main(){

    State *s1 = new State(2);
    State *s2 = new State(2);
    s1->board[0][0] = 1;
    s1->board[0][1] = 2;
    s1->board[1][0] = 3;
    s1->board[1][1] = 0;
    s2->board[0][0] = 1;
    s2->board[0][1] = 0;
    s2->board[1][0] = 3;
    s2->board[1][1] = 2;
    TH *t = new TH();
    std::cout  << "Esta  vacia la tabla: "  << t->isEmpty() << std::endl;
    std::cout  << std::endl;
    std::cout <<  "Funcion hash del primer estado: " << t->hashFunction(s1) << std::endl;
    t->insert(s1);
    std::cout <<  "Funcion hash del segundo estado: " << t->hashFunction(s1) << std::endl;
    t->insert(s2);
    for(int i=0;i<49;i++){

        if(!(t->sets[i])->isEmpty()){
            std::cout <<  "Lista " << i << std::endl;
            t->sets[i]->display();
        }
    }    
    return 0;
}