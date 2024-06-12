#include "Node.h"

Node::Node(){

    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
}

vector<vector<float>> Node::getSolutionMatrix(){
    return this->solutionMatrix;
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

void Node::setSolutionMatrix(vector<vector<float>> m){
    this->solutionMatrix = m;
}

void Node::setSolutionVector(vector<float> v){
    this->solutionVector = v;
}

void Node::setZinf(float zinf){
    this->zinf = zinf;
}

void Node::setZsup(float zsup){
    this->zsup = zsup;
}

void Node::setParent(Node* parent){
    this->parent = parent;
}

void Node::setLeft(Node* left){
    this->left = left;
}

void Node::setRight(Node* right){
    this->right = right;
}

void Node::getFirstMatrix(char* filename){

    Simplex* s = new Simplex(filename);
    solutionMatrix = s->initialA;
    solutionVector = s->solve();
    delete s;
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

void Node::getBranch(Simplex s1){

    Node* n1 = new Node();
    Node* n2 = new Node();
    left = n1;
    right = n2;
    Simplex s2 = s1.copy();
    int worstpos = worstFractionary(solutionVector);
    float up = ceil(solutionVector[worstpos]);
    float down = floor(solutionVector[worstpos]);
    s1.initialA = solutionMatrix;
    s1.insertConstraint(down,worstpos,1);
    n1->setSolutionMatrix(s1.initialA);
    n1->setSolutionVector(s1.solve());
    if(n1->getSolutionVector().empty()){

        delete n1;
        left = nullptr;
    }
    s2.initialA = solutionMatrix;
    s2.insertConstraint(up,worstpos,2);
    n2->setSolutionMatrix(s2.initialA);
    n2->setSolutionVector(s2.solve());
    if(n2->getSolutionVector().empty()){

        delete n2;
        right = nullptr;
    }
    return;

}



