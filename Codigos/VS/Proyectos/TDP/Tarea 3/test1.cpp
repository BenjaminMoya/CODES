#include "Node.h"

using namespace std;

int main() {
    
    Node* n = new Node();
    char filename[10] = "P1.txt";
    Simplex s = Simplex(filename);
    n->getFirstMatrix(filename);
    for(auto x : n->getSolutionVector()) {
        cout << x << " " ;
    }
    cout << endl;
    n->getBranch(s);
    for(auto x : (n->getLeft())->getSolutionVector()) {
        cout << x << " " ;
    }
    cout << endl;
    for(auto x : (n->getRight())->getSolutionVector()) {
        cout << x << " " ;
    }
    return 0;

}