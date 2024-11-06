#include <iostream>
#include "ColaSinNodo.h"
using namespace std;

int main(){


    Queue q(5);

    q.enqueue(10);
    q.enqueue(15);
    q.enqueue(20);
    q.display();

    q.dequeue();
    q.display();

    return 0;
}