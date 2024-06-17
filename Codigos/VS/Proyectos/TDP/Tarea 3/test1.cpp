#include "Tree.h"

using namespace std;

int main() {
    
    Node* n = new Node();
    char filename[10] = "P1.txt";
    Simplex* s = new Simplex(filename);
    n->getFirstMatrix(filename);
    Tree t = Tree(n);
    clock_t start = clock(); //Medicion temporal
    t.getBound();
    clock_t end = clock();
    double elapsed = end - start;
    for(auto x : t.getRoot()->getSolutionVector()){
        cout << x << " ";
    }
    return 0;

}