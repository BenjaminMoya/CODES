#include "Tree.h"

int main(){

    
    char filename[100]; 
    bool cond = true;
    int option;
    cout << "Solucionador 0-1 Knapsack" << endl;
    while(cond){
        cout << endl;
        cout << "1)Solucionar un archivo" << endl;
        cout << "2)Salir" << endl;
        cin >> option;
        if(option == 1){

            cout << "Ingrese el nombre del archivo con el problema: ";
            cin >> filename;
            Simplex* s =new Simplex(filename);
            Node* n = new Node();
            n->setSolutionVector(s->solve());
            n->getBranch(filename);
            Tree* t = new Tree(n);
            t->getBound(filename);
            for(auto x: t->getBestNode()->getSolutionVector()){
                cout << x << " ";
            }
        }

        if(option == 2){

            cout << "Saliendo..." << endl;
            cond = false;
        }
    }
    
    return 0;
}