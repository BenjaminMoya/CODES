#include "Node.h"

Node::Node(Simplex s){

    this->simplex = s;
    this->left = nullptr;
    this->right = nullptr;

}

Node::Node(){

    this->left = nullptr;
    this->right = nullptr;

}

float Node::getZinf(){
    return this->zinf;
}

float Node::getZsup(){
    return this->zsup;
}

Node* Node::getLeft(){
    return this->left;
}

Node* Node::getRight(){
    return this->right;
}

Simplex Node::getSimplex(){
    return this->simplex;
}

bool Node::getIntegerSolve(){
    return this->integerSolve;
}

void Node::setZinf(float newZinf){
    this->zinf = newZinf;
}

void Node::setZsup(float newZsup){
    this->zsup = newZsup;
}

void Node::setLeft(Node* newLeft){
    this->left = newLeft;
}

void Node::setRight(Node* newRight){
    this->right = newRight;
}

void Node::setSimplex(Simplex newSimplex){
    this->simplex = newSimplex;
}

void Node::setIntegerSolve(bool newIntegerSolve){
    this->integerSolve = newIntegerSolve;
}

void Node::getFirstMatrix(Simplex s){

    simplex.solve();
    zinf = floor(simplex.getSolution()[0]);
    zsup = simplex.getSolution()[0];
    return;
}

void Node::limits(){

    zinf = floor(simplex.getSolution()[0]);
    zsup = simplex.getSolution()[0];
    return;
}

bool Node::integerSolution(){

    for(int i = 1; i<simplex.getSolution().size();i++){

        if(fmod(simplex.getSolution()[i],1.0)!=0){

            return false;
        }
    }

    return true;

}
int Node::worstFractionary(vector<float> f){
    
    int worst = 0;
    for(int i = 1; i<f.size();i++){

        if(0.5-fmod(worst,1.0)>0.5-fmod(f[i],1.0)){

            worst = i;
        }
    }

    return worst;

}

void Node::getBranch(){

    Node* n1 = new Node();
    Node* n2 = new Node();
    left = n1;
    right = n2;
    int worstpos = worstFractionary(simplex.getSolution());
    float up = ceil(simplex.getSolution()[worstpos]);
    float down = floor(simplex.getSolution()[worstpos]);
    if(floor(simplex.getSolution()[worstpos])==simplex.getSolution()[worstpos]){

        return;
    }

    n1->setSimplex(simplex);
    n1->simplex.insertConstraint(down,worstpos,1);
    n1->simplex.solve();
    if(n1->simplex.getSolution().empty()){

        left = nullptr;
        delete n1;
    } else {
        n1->limits();
        if(n1->integerSolution()){

            n1->setIntegerSolve(true);
        }
    }

    n2->setSimplex(simplex);
    n2->simplex.insertConstraint(up,worstpos,2);
    n2->simplex.solve();
    if(n2->simplex.getSolution().empty()){

        left = nullptr;
        delete n2;
    } else {
        n2->limits();
        if(n2->integerSolution()){

            n2->setIntegerSolve(true);
        }
    }

    return;

}

Node Node::compare(Node* n1,Node* n2){

    if(n1->getZinf() > n2->getZsup()){

        return *n1;
    } else if(n2->getZinf() > n1->getZsup()){

        return *n2;
    } else {

        return *n1;
    }
}

void getBound(){

    //Falta hacer esta funcion sin necesidad de tener un contendor como tree y poder ahorrar memoria :p
}
Node::~Node(){
    delete left;
    delete right;
}
