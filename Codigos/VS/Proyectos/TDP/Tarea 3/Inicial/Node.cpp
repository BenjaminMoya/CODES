#include "Node.h"

Node::Node(Simplex s){

    this->simplex = s;
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

vector<float> Node::getSolutionVector(){
    return this->simplex.getSolution();
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

void Node::setSolutionVector(vector<float> newSolutionVector){
    this->solutionVector = newSolutionVector;
}  

void Node::getFirstMatrix(Simplex s){

    solutionVector = simplex.solve();
    zinf = floor(solutionVector[0]);
    zsup = solutionVector[0];
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
    
    int worst = 0;
    for(int i = 1; i<f.size();i++){

        if(0.5-fmod(worst,1.0)>0.5-fmod(f[i],1.0)){

            worst = i;
        }
    }

    return worst;

}

void Node::restrictions(int n,int pos, int type){

    this->simplex.insertConstraint(n,pos,type);
    return;
}

void Node::getSolve(){

    this->solutionVector = this->simplex.solve();
    return;

}

void Node::getBranch(){

    Node* n1 = new Node(getSimplex());
    Node* n2 = new Node(getSimplex());
    left = n1;
    right = n2;

    int worstpos = worstFractionary(solutionVector);
    cout << "Worst pos: " << worstpos << endl;
    float down = floor(solutionVector[worstpos]);
    cout << down << endl;
    float up = ceil(solutionVector[worstpos]);
    cout << up << endl;

    n1->restrictions(down,worstpos,1);
    cout << "N1" << endl;
    n1->getSimplex().printProblemMatrix();
    cout << endl;
    n1->getSolve();
    if(n1->getSolutionVector().empty()){

        left = nullptr;
        
    } else {
        n1->limits();
        if(n1->integerSolution()){

            n1->setIntegerSolve(true);
        }
    }

    n2->restrictions(up,worstpos,2);
    cout << "N2" << endl;
    n2->getSimplex().printProblemMatrix();
    cout << endl;
    n2->getSolve();
    if(n2->getSolutionVector().empty()){

        left = nullptr;
        
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

<<<<<<< HEAD:Codigos/VS/Proyectos/TDP/Tarea 3/Inicial/Node.cpp

=======
>>>>>>> 39d438d4ae4bdd9cc7ba8786c44d03251e94b7ac:Codigos/VS/Proyectos/TDP/Tarea 3/Node.cpp
Node::~Node(){
    delete left;
    delete right;
}