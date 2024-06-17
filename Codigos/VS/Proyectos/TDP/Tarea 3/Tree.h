#include "Node.h"

class Tree{

    private:

        Node* root;
        Node* best;
        vector<Node> generated;

    public:
    
        Tree(Node* n);
        Node* getRoot();
        Node* getBest();
        vector<Node> getGenerated();
        void setRoot(Node *newRoot);  
        void setBest(Node *newBest);
        void setGenerated(vector<Node> newNodes);
        void getBound();

};