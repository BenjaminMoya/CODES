#include <iostream>
using namespace std;

class Heap {

    public:
    
        int *arr;
        int capacity;
        int size; 
        Heap(int capacity);
        ~Heap();
        void push(int val);
        int pop();

};