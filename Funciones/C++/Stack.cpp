#include <iostream>
#include "Stack.h"
using namespace std;

Stack::Stack(int n){
    data = new State[n];
    size = n;
    top = -1;
}

Stack::~Stack(){
    delete [] data;

}

bool Stack::isEmpty(){
    return (top==-1);

}

void Stack::push(State *s){
    if (top==size-1) {
            State *data_tmp = new State[size*2]; 
            for (int i=0; i<size; i++) {
                data_tmp[i]=data[i]; 
            }
            delete[] data; 
            data=data_tmp; 
            size *=2; 
        }
        ++top;
        data[top]=*s; 

}

State *Stack::pop(){
    if (isEmpty()) {
            cout << "Stack Underflow" << endl;
            return nullptr;
        }
        return &(data[top--]);

}