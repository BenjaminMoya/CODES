#include "AvlNode.h"

AvlNode::AvlNode(State *state){
    //Se inicializa de los componentes de un AvlNode
    this->state = state;
    this->left = nullptr;
    this->right = nullptr;
    this->parent = nullptr;
    this->height = 1;
}

void AvlNode::ActHeight(){
    this->height = this->parent->height + 1;
}

AvlNode::~AvlNode(){
    //Se eleminan los componentes de un AvlNode
    delete state;
    delete left;
    delete right;
}