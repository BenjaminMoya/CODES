#include "Tree.h"

Tree::Tree(Node* n){

    this->root = n;
    this->best = nullptr;
    this->generated.insert(n);
    
}

Node* Tree::getRoot(){
    return this->root;
}

Node* Tree::getBest(){
    return this->best;
} 

Node* Tree::getBestInteger(){
    return this->bestInteger;
}

set<Node*> Tree::getGenerated(){
    return this->generated;
}

void Tree::setRoot(Node* newRoot){
    root = newRoot;
}

void Tree::setBest(Node* newBest){
    best = newBest;
}

void Tree::setBestInteger(Node* newBestInteger){
    bestInteger = newBestInteger;
}

void Tree::setGenerated(set<Node*> newNodes){
    generated = newNodes;
}

void Tree::getBound(){

    if(generated.empty()){

        return;
    }

    while(!generated.empty()){

        set<Node*>::iterator it = generated.begin();
        Node* aux = *(it);
        aux->getBranch();
        for(auto x: aux->getSolutionVector()){

            cout << x << " ";
        }
        cout << endl;
        if(aux->getLeft() != nullptr && aux->getRight() != nullptr){

            Node temp = aux->compare(aux->getLeft(),aux->getRight());
            if(best == nullptr){

                best = &temp;
                if(best->integerSolution()){

                    bestInteger = best;
                }
                generated.insert(best);

            } else if(best!=nullptr){

                if(best->getZinf() < temp.getZsup()){

                    if(best->getZsup() < temp.getZsup()){

                        best = &temp;
                    }

                    if((temp.integerSolution()) && bestInteger->getZsup() < temp.getZsup()){

                        bestInteger = &temp;
                    }
                    
                    generated.insert(&temp);
                }
            }
        }

        if(aux->getLeft() != nullptr && aux->getRight() == nullptr){

            if(best == nullptr){

                best = aux->getLeft();
                if(best->integerSolution()){

                    bestInteger = best;
                }
                generated.insert(best);

            } else if(best!=nullptr){

                if(best->getZinf() < aux->getLeft()->getZsup()){

                    if((aux->getLeft()->integerSolution()) && bestInteger->getZsup() < aux->getLeft()->getZsup()){

                        bestInteger = aux->getLeft();
                    }
                    generated.insert(aux->getLeft());
                }
            }
        }

        if(aux->getRight() != nullptr && aux->getLeft() == nullptr){

            if(best == nullptr){

                best = aux->getRight();
                if(best->integerSolution()){

                    bestInteger = best;
                }
                generated.insert(best);

            } else if(best!=nullptr){

                if(best->getZinf() < aux->getRight()->getZsup()){

                    if((aux->getRight()->integerSolution()) && bestInteger->getZsup() < aux->getRight()->getZsup()){

                        bestInteger = aux->getRight();
                    }
                    generated.insert(aux->getRight());
                }
            }
        }

        generated.erase(it);

    }
    
}