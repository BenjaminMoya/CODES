#include "Tree.h"

using namespace std;

int main() {
    
    char filename[10] = "P1.txt";
    Simplex s = Simplex("P1.txt");
    Node* n = new Node(s);
    n->getFirstMatrix(s);
    Tree t = Tree(n);
    clock_t start = clock(); //Medicion temporal
    t.getBound();
    clock_t end = clock();
    double elapsed = end - start;
    return 0;

}