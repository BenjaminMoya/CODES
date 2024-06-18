#include "Node.h"

Node::Node(){

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

Node* Node::getLeft(){
    return this->left;
}

Node* Node::getRight(){
    return this->right;
}

Simplex Node::getSolve(){
    return this->solve;
}

bool Node::getIntegerSolve(){
    return this->integerSolve;
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

void Node::setLeft(Node* newLeft){
    this->left = newLeft;
}

void Node::setRight(Node* newRight){
    this->right = newRight;
}

void Node::setSolve(Simplex newS){
    this->solve = newS;
}

void Node::setIntegerSolve(bool newIntegerSolve){
    this->integerSolve = newIntegerSolve;
}

void Node::getFirstMatrix(char* filename){

    Simplex s1 = Simplex(filename);
    solutionVector = s1.solve();
    zinf = floor(solutionVector[0]);
    zsup = solutionVector[0];
    solve = s1;
    return;
}

void Node::limits(){

    zinf = floor(solutionVector[0]);
    zsup = solutionVector[0];
    return;
}

bool Node::integerSolution(){

    for(int i = 1; i<solutionVector.size();i++){

        if(fmod(solutionVector[i],1.0)!=0){

            return false;
        }
    }

    return true;

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
    if(floor(solutionVector[worstpos])==solutionVector[worstpos]){

        return;
    }

    s1.insertConstraint(down,worstpos,1);
    n1->setSolve(s1);
    n1->setSolutionVector(s1.solve());
    if(n1->getSolutionVector().empty()){

        left = nullptr;
        delete n1;
    } 
    n1->limits();
    if(n1->integerSolution()){

        n1->setIntegerSolve(true);
    }

    s2.insertConstraint(up,worstpos,2);
    n2->setSolve(s2);
    n2->setSolutionVector(s2.solve());
    if(n2->getSolutionVector().empty()){

        right = nullptr;
        delete n2;
    }
    n2->limits();
    if(n2->integerSolution()){

        n2->setIntegerSolve(true);
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

