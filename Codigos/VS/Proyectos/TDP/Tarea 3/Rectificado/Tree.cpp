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

/*mejorar logica con la que se agrega o no un nodo a revisar  if(temp->getZsup() >= bestNode->getZinf() || aux->compareFractionary(temp,bestNode)->eq(temp) || aux->compareFractionary(temp,bestNode) == nullptr){
                        bestNode = aux->compareFractionary(temp,bestNode);
                        bestInteger = aux->compareInteger(temp2,bestInteger);
                        toVisit.insert(temp);
                    }
*/

void Tree::getBound(char* filename){ 
    
    while(!toVisit.empty()){
       
        if(bestNode != nullptr && bestInteger != nullptr && bestNode->eq(bestInteger)){

            break;
        }
        
        set<Node*>::iterator it = toVisit.begin();
        Node* aux = *(it);
        
        if(!checkVisit(aux)){//se cayo pipipip
            
            visited.insert(aux);
            aux->getBranch(filename);

            if(aux->getLeft() != nullptr && aux->getRight() != nullptr){
                
                Node* temp = aux->compareFractionary(aux->getRight(),aux->getLeft());
                Node* temp2 = aux->compareInteger(aux->getLeft(),aux->getRight());

                if(bestNode == nullptr){
                    
                    bestNode = temp;
                    bestInteger = temp2;
                    toVisit.insert(aux->getLeft());
                    toVisit.insert(aux->getRight());

                } else {
                    
                    bestNode = aux->compareFractionary(temp,bestNode);
                    bestInteger = aux->compareInteger(temp2,bestInteger);
                    toVisit.insert(aux->getLeft());
                    toVisit.insert(aux->getRight());
                    
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

                    bestNode = aux->compareFractionary(temp,bestNode);
                    bestInteger = aux->compareInteger(temp,bestInteger);
                    toVisit.insert(temp);
           
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
                    
                    bestNode = aux->compareFractionary(temp,bestNode);
                    bestInteger = aux->compareInteger(temp,bestInteger);
                    toVisit.insert(temp);
                
                }
            }
        }
        
        toVisit.erase(it);
    }

    return;
}

