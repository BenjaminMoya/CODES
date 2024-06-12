#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

int N = 50;
bool ady[50][50];

void generate_clique(int n){
    set<int> *R = new set<int>;
    while (R->size() < n) { // generando un subconjunto aleatorio de tamaño n
        R->insert(rand() % N);
    }

    for(auto i : *R) {
        for(auto j : *R) {
            if (i != j) {
                ady[i][j] = true;
                ady[j][i] = true;
            }
        }
    }

}

void generate_Noclique(int n){ // clique sin una arista
    set<int> *R = new set<int>;
    while (R->size() < n) { // generando un subconjunto aleatorio de tamaño n
        R->insert(rand() % N);
    }

    for(auto i : *R) {
        for(auto j : *R) {
            if (i != j) {
                ady[i][j] = true;
                ady[j][i] = true;
            }
        }
    }

    int i=-1;
    while (R->find(i) != R->end()) {
        i = rand() % N;
    }
    int j=-1;
    while (R->find(j) != R->end() || i == j) {
        j = rand() % N;
    }

    ady[i][j] = false;
    ady[j][i] = false;

}


int main() {
    std::ofstream file;
    int n=-1;
    while (n <= 0 || n > N) {
        cout << "Ingrese tamaño máximo clique (cota inferior): ";
        cin >> n;
    }
    cout<<endl;
    float p=-1.0;
    cout << "Ingrese probabilidad (valor entre 0 y 1) de arista: ";
    while(p<=0 || p>=1) {
      cin >> p;
    }
    cout<<endl;
    int dificultad=-1;
    while (dificultad < 0 || dificultad > 2) {
        cout << "Ingrese dificultad (0,1,2): ";
        cin >> dificultad;
    }
    cout<<endl;
    srand(0);



    
    
    for (int i = 0; i < N; i++) { // testeando todos las aristas
        for (int j = i+1; j < N; j++) {
            if (rand() < p * RAND_MAX) { // si es menor a la probabilidad, entonces es arista
                ady[i][j] = true;
                ady[j][i] = true;
            } else {
                ady[i][j] = false;
                ady[j][i] = false;
            }
        }
    }

    if (dificultad == 0) {
        generate_clique(n);
    } else if (dificultad == 1) {
        for (int k=0; k<=n; k++) {
          generate_clique(k);
        }
    } else if (dificultad == 2) {
        for (int k=0; k<=n; k++) {
              generate_clique(k);
        }
        
        for (int k=n; k<=n+5 && k<N; k++) {
              generate_Noclique(k);
        }

    }
    

    file.open("graph_"+to_string(n)+"_"+to_string(p)+"_"+to_string(dificultad)+".txt");
    file << N << std::endl;
    for (int i = 0; i < N; i++) {
        for (int j = i+1; j < N; j++) {
            if (ady[i][j]) {
                file << i << " " << j << endl;                
            }
        }
    }
    file.close();
    return 0;

}