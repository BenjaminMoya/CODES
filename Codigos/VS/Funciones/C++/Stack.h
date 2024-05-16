#include <iostream>
#include "State.h"
using namespace std; 

class Stack {
    public:
        State *data;
        int size; 
        int top;
        Stack(int n);
        ~Stack();
        bool isEmpty();
        void push(State *s);
        State *pop();
};