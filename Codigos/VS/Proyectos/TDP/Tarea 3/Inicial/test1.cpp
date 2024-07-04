#include "Tree.h"

using namespace std;

int main() {
    
    char filename[10] = "P1.txt";
    Simplex s = Simplex(filename);
    Node* n = new Node(s);
    n->getFirstMatrix(s);
    n->getBranch();
    n = n->getRight();
    n->getBranch();
    //Tree t = Tree(n);
    clock_t start = clock(); //Medicion temporal
    //t.getBound();
    clock_t end = clock();
    double elapsed = end - start;
    for(auto x: n->getSolutionVector()){

        cout << x << " ";
    }
    cout << endl;
    if(n->getLeft() == nullptr){

        cout << "1" << endl;
    }
    cout << endl;
    if(n->getRight() == nullptr){

        for(auto x: n->getRight()->getSolutionVector()){

            cout << x << " ";
        }
    } 
}