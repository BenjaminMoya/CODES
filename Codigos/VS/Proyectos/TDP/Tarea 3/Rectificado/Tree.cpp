#include "Tree.h"

Tree::Tree(Node* n){
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

set<Node*> Tree::getVisited(){
    return visited;
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

void Tree::setVisited(set<Node*> newVisited){
    visited = newVisited;
}

void Tree::setBestNode(Node* newBestNode){
    bestNode = newBestNode;
}

void Tree::setBestInteger(Node* newBestInteger){
    bestInteger = newBestInteger;
}

bool Tree::checkVisit(Node* n){

    if (visited.empty()) {

        return false;
    }

    for (auto it = visited.begin(); it != visited.end(); ++it) {

        Node* currentNode = *it;
        if(currentNode->getSolutionVector() == n->getSolutionVector()){

            return true;
        }
    }

    return false;
}

/*
    Todo arreglado. Queda optimizar implemenetando el cover cut el cual se vio en clases
    donde se hace una aproximacion con las mismas restricciones iniciales de las distintas variables sin peso
    por lo que tendremos una restriccion extra donde las variables no podran pasar ciertas normativas recortando la busqueda
*/

void Tree::getBound(char* filename){ 
    
    while(!toVisit.empty()){
        
        set<Node*>::iterator it = toVisit.begin();
        Node* aux = *(it);

        if(!checkVisit(aux)){

            visited.insert(aux);
            aux->getBranch(filename);

            if(aux->getLeft() != nullptr && aux->getRight() != nullptr){

                Node* temp = aux->compareSimple();
                Node* temp2 = aux->compareInteger(aux->getLeft(),aux->getRight());

                if(bestNode == nullptr){

                    bestNode = temp;
                    bestInteger = temp2;
                    toVisit.insert(temp);

                } else {
                
                    if(temp->getZsup() >= bestNode->getZinf()){ 
                    
                        bestNode = aux->compareFractionary(temp,bestNode);
                        bestInteger = aux->compareInteger(temp2,bestInteger);
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
                
                    if(temp->getZsup() >= bestNode->getZinf()){

                        bestNode = aux->compareFractionary(temp,bestNode);
                        bestInteger = aux->compareInteger(temp,bestInteger);
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
                
                    if(temp->getZsup() >= bestNode->getZinf()){

                        bestNode = aux->compareFractionary(temp,bestNode);
                        bestInteger = aux->compareInteger(temp,bestInteger);
                        toVisit.insert(temp);
                    }
                
                }
            }
        }
        
        toVisit.erase(it);
    }

}

