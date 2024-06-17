#include "Tree.h"

Tree::Tree(Node* n){

    this->root = n;
    this->generated.insert(n);
    
}

Node* Tree::getRoot(){
    return this->root;
}

Node* Tree::getBest(){
    return this->best;
} 

set<Node*> Tree::getGenerated(){
    return this->generated;
}

void Tree::setRoot(Node* newRoot){
    root = newRoot;
}

void Tree::setBest(Node* newBest){
    best = newBest;
}

void Tree::setGenerated(set<Node*> newNodes){
    generated = newNodes;
}

void Tree::getBound(){

    if(generated.empty()){

        return;
    }

    while(!generated.empty()){

        set<Node*>::iterator it = generated.begin();
        Node aux = **(it);
        aux.getBranch();
        if(aux.getLeft() != nullptr && aux.getLeft()->getZsup() >= best->getSolutionVector()[0]){

            if(aux.getLeft()->getZinf() > best->getSolutionVector()[0] || (!(best->integerSolution()) && aux.getLeft()->integerSolution())){

                best = aux.getLeft();
            }
            generated.insert((aux.getLeft()));
        }
        if(aux.getRight() != nullptr && aux.getRight()->getZsup() >= best->getSolutionVector()[0]){

            if(aux.getRight()->getZinf() > best->getSolutionVector()[0] || (!(best->integerSolution()) && aux.getRight()->integerSolution())){

                best = aux.getRight();
            }
            generated.insert((aux.getRight()));
        }
        generated.erase(it);

    }
    
}