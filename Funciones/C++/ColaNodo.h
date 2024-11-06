#include <iostream>
#include "Nodo.h"

class Queue {

    private:

        int size;
        Node* front;
        Node* rear;

    public:
        Queue(){

            front = nullptr;
            rear  = nullptr;
        }

        bool isEmpty(){

            return (front == nullptr);
        }

        void enqueue(int number){

            Node* newNode = new Node(number);
            if(isEmpty()){

                front = rear = newNode;
            } else {

                rear->next = newNode;
                rear = newNode;
            }

        }

        void dequeue(){

            if(isEmpty()){

                cout << "No data" << endl;
                return;
            }
            Node* temp = front;
            front = front -> next;
            delete temp;
        }

        void display(){

            if(isEmpty()){

                return;
            }
            Node* temp = front;
            cout << "Queue:" << endl;
            while(temp !=  nullptr){

                cout << temp->data << " ";
                temp = temp->next;
            }
        }
        ~Queue() {
            while (!isEmpty()) {
                dequeue();
            }
        }
};