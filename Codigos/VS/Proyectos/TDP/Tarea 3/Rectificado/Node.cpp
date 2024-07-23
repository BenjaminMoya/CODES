#include "Node.h"

Node::Node(){
    left = nullptr;
    right = nullptr;
}

Node::~Node(){
    delete left;
    delete right;
}

Node* Node::getLeft(){
    return left;
}

Node* Node::getRight(){
    return right;
}

float Node::getZinf(){
    return zinf;
}

float Node::getZsup(){
    return zsup;
}

bool Node::getIntegerSolve(){
    return integerSolve;
}

vector<float> Node::getSolutionVector(){
    return solutionVector;
}

void Node::setLeft(Node* left){
    this->left = left;
}

void Node::setRight(Node* right){
    this->right = right;
}

void Node::setSolutionVector(vector<float> newSolutionVector){
    solutionVector = newSolutionVector;
}

void Node::addRestriction(array<int,3> newRestriction){
    restrictions.insert(newRestriction);
}

void Node::setZinf(float newZinf){
    zinf = newZinf;
}

void Node::setZsup(float newZsup){
    zsup = newZsup;
}

void Node::setIntegerSolve(bool newIntegerSolve){
    integerSolve = newIntegerSolve;
}

void Node::setRestrictions(set<array<int,3>> newRestrictions){
    restrictions = newRestrictions;
}

int Node::worstFractionary(vector<float> f){
    
    int worst = 0;
    for(int i = 1; i<f.size();i++){

        if(fabs(0.5-fmod(worst,1.0)) > fabs(0.5-fmod(f[i],1.0))){

            worst = i;
        }
    }

    return worst;

}

void Node::setLimits(){

    zinf = floor(solutionVector[0]);
    zsup = solutionVector[0];
}

void Node::solveInteger(){

    for(int i = 1; i<solutionVector.size();i++){

        if(fmod(solutionVector[i],1.0)!=0){

            return;
        }
    }
    integerSolve = true;
    return;
}

Node* Node::compareSimple(){

    if(right->getZsup() != left->getZsup()){

        if(right->getZsup() > left->getZsup()){

            return right;
        } else {

            return left;
        }   

    } else {

        return nullptr;
    }

}

Node* Node::compareFractionary(Node* n1, Node* n2){ //Retorna el menos fraccionario

    int worstPos1 = worstFractionary(n1->getSolutionVector());
    int worstPos2 = worstFractionary(n2->getSolutionVector());
    if(fabs(0.5-fmod(n1->getSolutionVector()[worstPos1],1.0)) > fabs(0.5-fmod(n2->getSolutionVector()[worstPos2],1.0))){

        return n1;
    } else if(fabs(0.5-fmod(n1->getSolutionVector()[worstPos1],1.0)) < fabs(0.5-fmod(n2->getSolutionVector()[worstPos2],1.0))) {

        return n2;
    } else {

        return nullptr;
    }
}

Node* Node::compareInteger(Node* n1,Node* n2){ 

    if(n1->getIntegerSolve() && n2->getIntegerSolve()){

        if(n1->getZsup() > n2->getZsup()){

            return n1;
        } else if(n1->getZsup() < n2->getZsup()){

            return n2;
        } else {

            return nullptr;
        }

    } else if(!n1->getIntegerSolve() && n2->getIntegerSolve()) {

        return n2;
    } else if(n1->getIntegerSolve() && !n2->getIntegerSolve()){

        return n1;
    }

}

bool Node::eq(Node* n){

    if (n->getSolutionVector().size() != solutionVector.size()) {
        return false;
    }
    for (int i = 0; i < solutionVector.size(); ++i) {
        if (n->getSolutionVector()[i] != solutionVector[i]) {
            return false;
        }
    }
    return true;
}

void Node::getBranch(char* filename){

    int worstpos = worstFractionary(solutionVector);
    int down = floor(solutionVector[worstpos]);
    int up = ceil(solutionVector[worstpos]);
    Simplex* s1 = new Simplex(filename);
    Simplex* s2 = new Simplex(filename);
    
    if(restrictions.empty()){

        s1->insertConstraint(down,worstpos,1);
        if(!(s1->solve().empty())){

            array<int,3> a = {down,worstpos,1};
            Node *aux = new Node();
            aux->setSolutionVector(s1->getSolution());
            aux->solveInteger();
            aux->setLimits();
            aux->addRestriction(a);
            left = aux;
        }

        s2->insertConstraint(up,worstpos,2);
        if(!(s2->solve().empty())){

            array<int,3> a = {up,worstpos,2};
            Node *aux = new Node();
            aux->setSolutionVector(s2->getSolution());
            aux->solveInteger();
            aux->setLimits();
            aux->addRestriction(a);
            right = aux;
        }

        delete s1;
        delete s2;
        return;
    }

    if(!(restrictions.empty())){
        
        for(auto x: restrictions){
            
            s1->insertConstraint(get<0>(x),get<1>(x),get<2>(x));
            s2->insertConstraint(get<0>(x),get<1>(x),get<2>(x));
        }

        s1->insertConstraint(down,worstpos,1);
        if(!(s1->solve().empty())){

            array<int,3> a = {down,worstpos,1};
            Node *aux = new Node();
            aux->setSolutionVector(s1->getSolution());
            aux->solveInteger();
            aux->setLimits();
            aux->addRestriction(a);
            left = aux;
        }

        s2->insertConstraint(up,worstpos,2);
        if(!(s2->solve().empty())){

            array<int,3> a = {up,worstpos,2};
            Node *aux = new Node();
            aux->setSolutionVector(s2->getSolution());
            aux->solveInteger();
            aux->setLimits();
            aux->addRestriction(a);
            right = aux;
        }

        delete s1;
        delete s2;
        return;
    }

}
