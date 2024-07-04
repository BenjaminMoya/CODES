#include "Simplex.h"
using namespace std;

class Node{

    private:

        set<array<int,3>> restrictions;
        vector<float> solutionVector;
        Node* left;
        Node* rigth;
    public:

        Node();
        ~Node();
        Node* getLeft();
        Node* getRigth();
        set<array<int,3>> getRestrictions();
        vector<float> getSolutionVector();
        void setLeft(Node* left);
        void setRigth(Node* rigth);
        void setRestrictions(set<array<int,3>> newRestrictions);
        void setSolutionVector(vector<float> newSolutionVector);
        void addRestriction(array<int,3> newRestriction);
        int worstFractionary(vector<float> f);
        void getBranch(char* filename);
        
};