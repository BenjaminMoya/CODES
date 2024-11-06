#include <iostream>
#include "Puzle.h"
using namespace std;

void Puzzle::solve(){

    open->push(board);
    all->push(board);
    while(!open->isEmpty()){

        State *e = open->pop();
        if(e->isSolution()){

            cout << "Encontramos la solucion" << endl;
            e->print();
            return;
        }
        all->push(e);

        State e_up=e->up();
        if (e_up!=nullptr && !all->contains(e_up)){

            open->push(e_up);
        }

        State e_down=e->down();
        if (e_down!=nullptr && !all->contains(e_down)){

            open->push(e_down);
        }

        State e_rigth=e->rigth();
        if (e_rigth!=nullptr && !all->contains(e_rigth)){

            open->push(e_rigth);
        }

        State e_left=e->left();
        if (e_left!=nullptr && !all->contains(e_left)){

            open->push(e_left);
        }

    }
    
}