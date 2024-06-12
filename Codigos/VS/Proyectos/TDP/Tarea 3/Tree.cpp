#include "Tree.h"

Tree::Tree(){

    this->root = NULL;
    this->best = NULL;
}

Node* Tree::getRoot(){
    return this->root;
}

Node* Tree::getBest(){
    return this->best;
} 

vector<Node> Tree::getNodes(){
    return this->nodes;
}

void Tree::setRoot(Node* root){
    this->root = root;
}

void Tree::setBest(Node* best){
    this->best = best;
}

void Tree::setNodes(vector<Node> nodes){
    this->nodes = nodes;
}

