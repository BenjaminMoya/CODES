#include "Node.h"

Node::Node(){

    this->parent = nullptr;
    this->left = nullptr;
    this->right = nullptr;

}

vector<float> Node::getSolutionVector(){
    return this->solutionVector;
}

float Node::getZinf(){
    return this->zinf;
}

float Node::getZsup(){
    return this->zsup;
}

Node* Node::getParent(){
    return this->parent;
}

Node* Node::getLeft(){
    return this->left;
}

Node* Node::getRight(){
    return this->right;
}

Simplex Node::getSolve(){
    return this->solve;
}

void Node::setSolutionVector(vector<float> newSolutionVector){
    this->solutionVector = newSolutionVector;
}

void Node::setZinf(float newZinf){
    this->zinf = newZinf;
}

void Node::setZsup(float newZsup){
    this->zsup = newZsup;
}

void Node::setParent(Node* newParent){
    this->parent = newParent;
}

void Node::setLeft(Node* newLeft){
    this->left = newLeft;
}

void Node::setRight(Node* newRight){
    this->right = newRight;
}

void Node::setSolve(Simplex newS){
    this->solve = newS;
}

void Node::getFirstMatrix(char* filename){

    Simplex s1 = Simplex(filename);
    solutionVector = s1.solve();
    zinf = floor(solutionVector[0]);
    zsup = solutionVector[0];
    solve = s1;
    return;
}

int Node::worstFractionary(vector<float> f){
    
    float worst = 0;
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
    Simplex s1 = solve.copy();
    Simplex s2 = solve.copy();
    left = n1;
    right = n2;
    int worstpos = worstFractionary(solutionVector);
    float up = ceil(solutionVector[worstpos]);
    float down = floor(solutionVector[worstpos]);
    s1.insertConstraint(down,worstpos,1);
    n1->setSolve(s1);
    n1->setSolutionVector(s1.solve());
    if(n1->getSolutionVector().empty()){

        left = nullptr;
        delete n1;
    } else {

        n1->setParent(this);
    }
    s2.insertConstraint(up,worstpos,2);
    n2->setSolve(s2);
    n2->setSolutionVector(s2.solve());
    if(n2->getSolutionVector().empty()){

        right = nullptr;
        delete n2;
    } else {

        n2->setParent(this);
    } 
    return;

}



