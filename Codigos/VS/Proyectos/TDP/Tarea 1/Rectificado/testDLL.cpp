#include <iostream>
#include "DLL.h"

int main(){

    State *s1 = new State(2);
    State *s2 =  new State(2);
    s2->board[0][0] = 1;
    s2->board[0][1] = 1;
    s2->board[1][0] = 1;
    s2->board[1][1] = 1;
    DLL *l = new DLL(s1);
    std::cout  << "La lista esta vacia: " << l->isEmpty() << std::endl;
    l->display();
    std::cout  <<  std::endl;
    l->insertFront(s1);
    l->display();
    std::cout  <<  std::endl;
    l->removeFront();
    l->display();
    std::cout  <<  std::endl;
    l->insertBack(s1);
    l->display();
    std::cout  <<  std::endl;
    l->removeBack();
    std::cout  << "El elemento por defecto esta en la lista: " << l->find(s1) << std::endl;
    l->insertBack(s2);
    l->insertBack(s1);
    l->display();
    std::cout  <<  std::endl;
    std::cout << "Se remueve  el elemento del medio" << std::endl;
    std::cout  <<  std::endl;
    l->remove(s2);
    l->display();
    std::cout  <<  std::endl;
    std::cout  << "Se encuentra el mejor estado (Resultados la simulacion)" << std::endl;
    std::cout  <<  std::endl;
    State *s3 = l->findBest();
    s3->print();
    return 0;
}