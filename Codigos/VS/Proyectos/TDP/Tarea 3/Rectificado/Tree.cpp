#include "Tree.h"

Tree::Tree(Node *n){
    bestNode = nullptr;
    bestInteger = nullptr;
    toVisit.insert(n);
} 

Tree::~Tree(){
    delete bestNode;
    delete bestInteger;
}

set<Node*> Tree::getToVisit(){
    return toVisit;
}

Node* Tree::getBestNode(){
    return bestNode;
}

Node* Tree::getBestInteger(){
    return bestInteger;
}

void Tree::setToVisit(set<Node*> newToVisit){
    toVisit = newToVisit;
}

void Tree::setBestNode(Node* newBestNode){
    bestNode = newBestNode;
}

void Tree::setBestInteger(Node* newBestInteger){
    bestInteger = newBestInteger;
}

void Tree::getBound(char* filename){

    while(!toVisit.empty()){

        set<Node*>::iterator it = toVisit.begin();
        Node* aux = *(it);
        aux->getBranch(filename);
        if(aux->getLeft() != nullptr && aux->getRight() != nullptr){
            
            Node* temp = aux->compareSimple();
            if(bestNode == nullptr){

                bestNode = temp;
                if(temp->getIntegerSolve()){

                    bestInteger = temp;
                }
                toVisit.insert(temp);

            } else {
                
                if(temp->getZsup() > bestNode->getZinf()){

                    bestNode = aux->compareFractionary(temp,bestNode);
                    if(temp->getIntegerSolve() && temp->getZsup() > bestInteger->getZsup()){

                        bestInteger = temp;
                    }
                    toVisit.insert(temp);
                }
                
            }
        }

        if(aux->getLeft() != nullptr && aux->getRight() == nullptr){
            
            Node* temp = aux->getLeft();
            if(bestNode == nullptr){

                bestNode = temp;
                if(temp->getIntegerSolve()){

                    bestInteger = temp;
                }
                toVisit.insert(temp);

            } else {
                
                if(temp->getZsup() > bestNode->getZinf()){

                    bestNode = aux->compareFractionary(temp,bestNode);
                    if(temp->getIntegerSolve() && temp->getZsup() > bestInteger->getZsup()){

                        bestInteger = temp;
                    }
                    toVisit.insert(temp);
                }
                
            }
        }

        if(aux->getLeft() == nullptr && aux->getRight() != nullptr){
            
            Node* temp = aux->getRight();
            if(bestNode == nullptr){

                bestNode = temp;
                if(temp->getIntegerSolve()){

                    bestInteger = temp;
                }
                toVisit.insert(temp);

            } else {
                
                if(temp->getZsup() > bestNode->getZinf()){

                    bestNode = aux->compareFractionary(temp,bestNode);
                    if(temp->getIntegerSolve() && temp->getZsup() > bestInteger->getZsup()){

                        bestInteger = temp;
                    }
                    toVisit.insert(temp);
                }
                
            }
        }
        toVisit.erase(it);
    }

}

