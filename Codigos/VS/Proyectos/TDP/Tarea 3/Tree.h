#include "Node.h"

class Tree{

    private:

        Node* root;
        Node* best;
        set<Node*> generated;

    public:
    
        Tree(Node* n);
        Node* getRoot();
        Node* getBest();
        set<Node*> getGenerated();
        void setRoot(Node* newRoot);  
        void setBest(Node* newBest);
        void setGenerated(set<Node*> newNodes);
        void getBound();

};