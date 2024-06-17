#include "Tree.h"

using namespace std;

int main() {
    
    Node* n = new Node();
    char filename[10] = "P1.txt";
    n->getFirstMatrix(filename);
    Tree t = Tree(n);
    clock_t start = clock(); //Medicion temporal
    t.getBound();
    clock_t end = clock();
    double elapsed = end - start;
    return 0;

}