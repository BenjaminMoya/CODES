#include "Simplex.h"
using namespace std;

class Node{

    private:

        vector<float> solutionVector;
        Simplex simplex;
        float zinf;
        float zsup;
        Node* left;
        Node* right;
        bool integerSolve;

    public:

        Node(Simplex s);
        Simplex getSimplex();
        vector<float> getSolutionVector();
        float getZinf();
        float getZsup();
        Node* getLeft();
        Node* getRight();
        bool getIntegerSolve();
        void setSimplex(Simplex newSimplex);
        void setSolutionVector(vector<float> newSolutionVector);
        void setZinf(float newZinf);
        void setZsup(float newZsup);
        void setParent(Node* newParent);
        void setLeft(Node* newLeft);
        void setRight(Node* newRight);
        void setIntegerSolve(bool newIntegerSolve);
        void getFirstMatrix(Simplex s);
        int worstFractionary(vector<float> f);
        void limits();
        bool integerSolution();
        void restrictions(int n,int pos,int type);
        void getSolve();
        void getBranch();
        Node compare(Node *n1,Node *n2);
        ~Node();
        
};