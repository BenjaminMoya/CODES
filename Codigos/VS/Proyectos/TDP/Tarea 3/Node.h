#include "Simplex.h"
using namespace std;

class Node{

    private:

        vector<float> solutionVector;
        Simplex solve;
        float zinf;
        float zsup;
        Node* left;
        Node* right;
        bool integerSolve;

    public:

        Node();
        vector<float> getSolutionVector();
        Simplex getSolve();
        float getZinf();
        float getZsup();
        Node* getParent();
        Node* getLeft();
        Node* getRight();
        bool getIntegerSolve();
        void setSolutionVector(vector<float> newSolutionVector);
        void setSolve(Simplex newSolve);
        void setZinf(float newZinf);
        void setZsup(float newZsup);
        void setParent(Node* newParent);
        void setLeft(Node* newLeft);
        void setRight(Node* newRight);
        void setIntegerSolve(bool newIntegerSolve);
        void getFirstMatrix(char *filename);
        int worstFractionary(vector<float> f);
        void limits();
        bool integerSolution();
        void getBranch();
        Node* compare(Node *n1,Node *n2);
        
};