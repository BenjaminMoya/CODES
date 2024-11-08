#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <set>
#include <sstream>
#include <cmath>
#include <utility>
#include <ctime>
#define EPS 1.0e-6

/*
    Descripcion de la clase Simplex:
    Esta clase representa un solucionador de problemas de optimizacion
    lineal con variables reales [x1,....,xn]., mediante el metodo Simplex. 
    este busca maximizar una funcion con restricciones asociadas.
*/
class Simplex
{
private:
    int m; // Numero de restricciones
    int n; // Numero de variables
    bool isSolved;
    int icase;
    std::vector<int> izrov;
    std::vector<int> iposv;
    std::vector<float> solution;
    int simplx();
    void maxValue(int mm, std::vector<int> ll, int nll, int iabf, int *kp, float *bmax);
    void locatePivot(int *ip, int kp);
    void exchangeParameters(int i1, int k1, int ip, int kp);
    float fabs(float x);

public:
    std::vector<std::vector<float>> initialA; // Matriz del problema.
    std::vector<std::vector<float>> a; // Matriz en donde se genera la solucion.
    int m1; // numero de restricciones <=
    int m2; // ... >=
    int m3; // igualdad

    Simplex();
    Simplex(std::string file_name);
    Simplex(std::vector<std::vector<float>> a, int m1, int m2, int m3);
    ~Simplex();
    std::vector<float> solve(); // el retorno es [Z, x1, x2, ..., xn]
    void insertConstraint(float b, int var, int type);
    Simplex copy();
    std::vector<float> getSolution();
    void printProblemMatrix();
    void printSolution();
};