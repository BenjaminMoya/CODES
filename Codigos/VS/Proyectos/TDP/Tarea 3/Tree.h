#include "Node.h"

class Tree{

    private:

        Node* root;
        Node* best;
        vector<Node> nodes;
    public:
    
        Tree();
        Node* getRoot();
        Node* getBest();
        vector<Node> getNodes();
        void setRoot(Node* root);  
        void setBest(Node* best);
        void setNodes(vector<Node> nodes);

};