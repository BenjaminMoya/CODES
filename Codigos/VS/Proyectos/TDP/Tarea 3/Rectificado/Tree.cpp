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

    //Verifica si la solucion ya se reviso en la lista de visitados
    if(visited.empty()){

        return false;
    }

    auto it1 = visited.begin();
    auto it2 = visited.rbegin();

    if((*it1)->eq(*it2)) {

        if((*it1)->eq(n)){

            return true;
        } else {

            return false;
        }
    }

    while(it1 != visited.end() && it2 != visited.rend()){

        if((*it1)->eq(n)){

            return true;
        }

        if((*it2)->eq(n)){

            return true;
        }
        it1++;
        it2++;
    }

    return false;
}

/*
    Ver porque agrega soluciones que no deberia agregar
    4.4 1 0.2 1 3 1 1 0 4 1 0 1 4 1 0 1 5 1 1 0.666667 5 1 1 0.666667 4.4 1 0.2 1 3 1 1 0 5 1 1 0.666667. Hay que quitar las
    ultimas rpeticiones, verificando las condicioonales.

    Ahora se cae, parece ser por mala gestion de los iteradores no tanto de memoria,}
    revisar con valgrind.
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
                if(temp == nullptr){

                    temp = aux->compareFractionary(aux->getLeft(),aux->getRight());
                    if(temp == nullptr){

                        temp = aux->getLeft();
                    }
                }
                Node* temp2 = aux->compareInteger(aux->getLeft(),aux->getRight());
                if(temp2 == nullptr){

                    temp2 = aux->getLeft();
                }

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

