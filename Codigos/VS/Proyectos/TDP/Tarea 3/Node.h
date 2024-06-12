#include "Simplex.h"
using namespace std;

class Node{

    private:

        vector<vector<float>>solutionMatrix;
        vector<float> solutionVector;
        float zinf;
        float zsup;
        Node* parent;
        Node* left;
        Node* right;

    public:

        Node();
        vector<vector<float>> getSolutionMatrix();
        vector<float> getSolutionVector();
        float getZinf();
        float getZsup();
        Node* getParent();
        Node* getLeft();
        Node* getRight();
        void setSolutionMatrix(vector<vector<float>> m);
        void setSolutionVector(vector<float> v);
        void setZinf(float zinf);
        void setZsup(float zsup);
        void setParent(Node* parent);
        void setLeft(Node* left);
        void setRight(Node* right);
        void getFirstMatrix(char *filename);
        int worstFractionary(vector<float> f);
        void getBranch(Simplex s1);
        

};