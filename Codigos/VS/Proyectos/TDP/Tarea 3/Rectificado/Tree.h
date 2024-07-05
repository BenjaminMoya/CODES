#include "Node.h"

class Tree{

    private:

        set<Node*> toVisit;
        Node* bestNode;
        Node* bestInteger;

    public:

        Tree(Node *n);
        ~Tree();
        set<Node*> getToVisit();
        Node* getBestNode();
        Node* getBestInteger();
        void setToVisit(set<Node*> newToVisit);
        void setBestNode(Node* newBestNode);
        void setBestInteger(Node* newBestInteger);
        void getBound(char* filename);

};