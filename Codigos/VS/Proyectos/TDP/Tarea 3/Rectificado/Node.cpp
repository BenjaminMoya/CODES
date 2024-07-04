#include "Node.h"

Node::Node(){
    left = nullptr;
    rigth = nullptr;
}

Node::~Node(){
    delete left;
    delete rigth;
}

Node* Node::getLeft(){
    return left;
}

Node* Node::getRigth(){
    return rigth;
}

vector<float> Node::getSolutionVector(){
    return solutionVector;
}

void Node::setLeft(Node* left){
    this->left = left;
}

void Node::setRigth(Node* rigth){
    this->rigth = rigth;
}

void Node::setSolutionVector(vector<float> newSolutionVector){
    solutionVector = newSolutionVector;
}

void Node::addRestriction(array<int,3> newRestriction){
    restrictions.insert(newRestriction);
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
            aux->addRestriction(a);
            left = aux;
        }

        s2->insertConstraint(up,worstpos,2);
        if(!(s2->solve().empty())){

            array<int,3> a = {up,worstpos,2};
            Node *aux = new Node();
            aux->setSolutionVector(s2->getSolution());
            aux->addRestriction(a);
            rigth = aux;
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
            aux->setSolutionVector(s1->solve());
            aux->addRestriction(a);
            left = aux;
        }

        s2->insertConstraint(up,worstpos,2);
        if(!(s2->solve().empty())){

            array<int,3> a = {up,worstpos,2};
            Node *aux = new Node();
            aux->setSolutionVector(s2->solve());
            aux->addRestriction(a);
            rigth = aux;
        }

        delete s1;
        delete s2;
        return;
    }

    
}
