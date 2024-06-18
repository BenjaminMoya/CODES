#include "Node.h"

class Tree{

    private:

        Node* root;
        Node* best;
        Node* bestInteger;
        set<Node*> generated;

    public:
    
        Tree(Node* n);
        Node* getRoot();
        Node* getBest();
        Node* getBestInteger();
        set<Node*> getGenerated();
        void setRoot(Node* newRoot);  
        void setBest(Node* newBest);
        void setGenerated(set<Node*> newNodes);
        void setBestInteger(Node* newBestInteger);  
        void getBound();

};