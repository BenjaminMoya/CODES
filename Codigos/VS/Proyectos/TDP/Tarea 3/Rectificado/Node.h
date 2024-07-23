#include "Simplex.h"
using namespace std;

class Node{

    private:

        set<array<int,3>> restrictions;
        vector<float> solutionVector;
        float zinf;
        float zsup;
        bool integerSolve = false;
        Node* left;
        Node* right;

    public:

        Node();
        ~Node();
        Node* getLeft();
        Node* getRight();
        float getZinf();
        float getZsup();
        bool getIntegerSolve();
        set<array<int,3>> getRestrictions();
        vector<float> getSolutionVector();
        void setLeft(Node* left);
        void setRight(Node* rigth);
        void setZinf(float newZinf);
        void setZsup(float newZsup);
        void setIntegerSolve(bool newIntegerSolve);
        void setRestrictions(set<array<int,3>> newRestrictions);
        void setSolutionVector(vector<float> newSolutionVector);
        void addRestriction(array<int,3> newRestriction);
        int worstFractionary(vector<float> f);
        void setLimits();
        void solveInteger();
        Node* compareSimple();
        Node* compareFractionary(Node* n1,Node* n2);
        Node* compareInteger(Node* n1,Node* n2);
        bool eq(Node* n);
        void getBranch(char* filename);
        
};