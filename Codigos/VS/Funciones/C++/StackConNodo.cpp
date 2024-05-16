#include <iostream>
#include "Nodo.h"
using namespace std;

class Stack{

    public:
        
        int size;
        Node* top;

    Stack(){

        top = nullptr;
    }
    bool isEmpty(){

        return((top->data)==-1);
    }
    void push(int number){

        Node* newNode = new Node(number);
        if(isEmpty()){

            top = newNode;
            size+=1;
        } else {

            newNode -> next = top;
            top = newNode;
            size+=1;
        }
    }
    void pop(){

        if(isEmpty()){

            cout << "No data" << endl;
            return;
        }
        Node* temp = top;
        delete top;
        top = temp -> next;
        delete temp;
        size-=1;

    }

    void display(){

        if(isEmpty()){

            cout << "No data" << endl;
            return;
        }
        Node* temp = top;
        cout << "Queue:" << endl;
        while(temp != nullptr){

            cout << temp -> data << " ";
            temp = temp -> next;
        }
    }
    ~Stack(){
        while(!isEmpty()){

            pop();
        }
    }
    
};

