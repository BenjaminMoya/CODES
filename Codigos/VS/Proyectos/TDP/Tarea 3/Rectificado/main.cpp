#include "Node.h"

int main(){

    char filename[10] = "P1.txt";
    Simplex* s =new Simplex("P1.txt");
    Node* n = new Node();
    n->setSolutionVector(s->solve());
    n->getBranch(filename);
    for(auto x: n->getRigth()->getSolutionVector()){
        cout<< x <<" ";
    }
    return 0;
}