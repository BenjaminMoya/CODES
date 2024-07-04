#include "Simplex.h"
using namespace std;

class Node{

    private:

        Simplex simplex;
        float zinf;
        float zsup;
        Node* left;
        Node* right;
        bool integerSolve;

    public:

        Node(Simplex s);
        Node();
        Simplex getSimplex();
        float getZinf();
        float getZsup();
        Node* getParent();
        Node* getLeft();
        Node* getRight();
        bool getIntegerSolve();
        void setSimplex(Simplex newSimplex);
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
        void getBranch();
        Node compare(Node *n1,Node *n2);
        ~Node();
        
};