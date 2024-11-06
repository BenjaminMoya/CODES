#include <iostream>
using namespace  std;

class Node{

    public:

        int data;
        Node* next;

    Node(int number){

        data = number;
        next = nullptr;
    }

};