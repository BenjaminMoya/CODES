#include <iostream>
using namespace std;
class Queue{

    private:
        int* arr;
        int capacity;
        int front;
        int rear;

    public:
        Queue(int size){

            capacity = size;
            arr = new int[capacity];
            front  = rear = -1;
        }
        ~Queue() {
            delete[] arr;
        }
        bool isEmpty(){

            return(front==-1);
        }

        bool isFull(){

            return((rear+1)%capacity==front);
        }

        void enqueue(int val){
            
            if(isFull()){

                int newCapacity = capacity * 2;
                int* newArr = new int[newCapacity];

                int i  = front;
                int j = 0;
                while(i != rear){

                    newArr[j++] = arr[i];
                    i = (i + 1) % capacity;
                }

                newArr[j] = arr[rear];

                front = 0;
                rear = j;

                delete[] arr;

                capacity = newCapacity;
                arr = newArr;
            }
            if(isEmpty()){

                front = rear = 0;
            } else {

                rear = (rear + 1) % capacity;
            }
            arr[rear] = val;
        }
        void dequeue(){

            if(isEmpty()){

                cout << "No data" << endl;
                return;
            }
            int removedValue = arr[front];
            if(front == rear){

                front = rear = -1;
            }else{

                front = (front + 1) % capacity;
            }
        }
        void display(){

            if(isEmpty()){

                cout << "No data" << endl;
                return;
            }
            cout << "Queue:";
            int i = front;
            while(i != rear){

                cout << arr[i]  << " ";
                i= (i + 1) % capacity;
            }
            cout << arr[rear] << endl;
        }
};