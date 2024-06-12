#include <iostream>
#include "Node.h"

int main(){

    State *s1 = new State(2);
    s1->board[0][0] = 1;
    s1->board[0][1] = 1;
    s1->board[1][0] = 1;
    s1->board[1][1] = 1;
    State *s2 = new State(2);
    Node *n1 = new Node(s1);
    Node *n2 = new Node(s1);
    Node *n3 = new Node(s2);
    std::cout << "Verificacion de igualdad entre nodos:" << std::endl;
    std::cout << std::endl;
    std::cout << "N1 = N2:";
    std::cout << n1->eq(n2) << std::endl;
    std::cout << "N1 = N3:";
    std::cout << n1->eq(n3) << std::endl;
    return 0;
}