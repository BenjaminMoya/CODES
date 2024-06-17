#include "Tree.h"

Tree::Tree(Node* n){

    this->root = *n;
    this->best = *n;
    this->generated.insert(n);
    
}

Node Tree::getRoot(){
    return this->root;
}

Node Tree::getBest(){
    return this->best;
} 

set<Node*> Tree::getGenerated(){
    return this->generated;
}

void Tree::setRoot(Node newRoot){
    root = newRoot;
}

void Tree::setBest(Node newBest){
    best = newBest;
}

void Tree::setGenerated(set<Node*> newNodes){
    generated = newNodes;
}

void Tree::getBound(){

    if(generated.empty()){

        return;
    }
    Node aux = **generated.begin();
    aux.getBranch();
    generated.erase(generated.begin());
    /*
    if(aux->getLeft() != nullptr && aux->getLeft()->getSolutionVector()[0] < best->getSolutionVector()[0]){

        if(aux->getLeft()->getZinf() > best->getSolutionVector()[0]){

            best = aux->getLeft();
        }
        generated.push_back((aux->getLeft()));
    }
    if(aux->getRight() != nullptr && aux->getRight()->getSolutionVector()[0] < best->getSolutionVector()[0]){

        if(aux->getRight()->getZinf() > best->getSolutionVector()[0]){

            best = aux->getRight();
        }
        generated.push_back((aux->getRight()));
    }
    */
    getBound();
}