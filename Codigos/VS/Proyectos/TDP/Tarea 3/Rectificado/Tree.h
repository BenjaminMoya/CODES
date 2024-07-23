#include "Node.h"

class Tree{

    private:

        set<Node*> toVisit;
        set<Node*> visited;
        Node* bestNode;
        Node* bestInteger;

    public:

        Tree(Node* n);
        ~Tree();
        set<Node*> getToVisit();
        set<Node*> getVisited();
        Node* getBestNode();
        Node* getBestInteger();
        void setToVisit(set<Node*> newToVisit);
        void setVisited(set<Node*> newVisited);
        void setBestNode(Node* newBestNode);
        void setBestInteger(Node* newBestInteger);
        bool checkVisit(Node* n);
        void getBound(char* filename);

};