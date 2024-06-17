#include "Simplex.h"
using namespace std;

class Node{

    private:

        vector<float> solutionVector;
        Simplex solve;
        float zinf;
        float zsup;
        Node* parent;
        Node* left;
        Node* right;

    public:

        Node();
        vector<float> getSolutionVector();
        Simplex getSolve();
        float getZinf();
        float getZsup();
        Node* getParent();
        Node* getLeft();
        Node* getRight();
        void setSolutionVector(vector<float> newSolutionVector);
        void setSolve(Simplex newSolve);
        void setZinf(float newZinf);
        void setZsup(float newZsup);
        void setParent(Node* newParent);
        void setLeft(Node* newLeft);
        void setRight(Node* newRight);
        void getFirstMatrix(char *filename);
        int worstFractionary(vector<float> f);
        void getBranch();
        
};