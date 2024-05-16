#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100

// Función para realizar el recorrido BFS con matriz de adyacencia
void BFS(int matrizAdy[MAX_VERTICES][MAX_VERTICES], int numVertices, int origen) {
    bool visitados[MAX_VERTICES] = { false };
    int cola[MAX_VERTICES];
    int frente = 0;
    int final = 0;

    // Marcar el vértice de origen como visitado y encolarlo
    visitados[origen] = true;
    cola[final++] = origen;

    printf("Recorrido BFS desde el vértice %d: ", origen);

    while (frente != final) {
        int actual = cola[frente++];
        printf("%d ", actual);

        // Recorrer los vértices adyacentes al vértice actual
        for (int i = 0; i < numVertices; i++) {
            if (matrizAdy[actual][i] == 1 && !visitados[i]) {
                visitados[i] = true;
                cola[final++] = i;
            }
        }
    }

    printf("\n");
}

int main() {
    int numVertices = 6;

    // Inicializar la matriz de adyacencia con todos los elementos establecidos en 0
    int matrizAdy[MAX_VERTICES][MAX_VERTICES] = { 0 };

    // Agregar conexiones entre los vértices
    matrizAdy[0][1] = 1;
    matrizAdy[0][2] = 1;
    matrizAdy[1][3] = 1;
    matrizAdy[2][3] = 1;
    matrizAdy[2][4] = 1;
    matrizAdy[3][4] = 1;
    matrizAdy[3][5] = 1;

    int origen = 0;

    // Realizar el recorrido BFS
    BFS(matrizAdy, numVertices, origen);

    return 0;
}

/*int main(int argc, char *argv[]) {
  Grafo *g;
  // Lee el nombre del archivo
  char *archivo = argv[1];
  float arreglo;
  int *arreglo2;
  // Lee el valor del vertice origen y vertice destino
  char *or = argv[2];
  char *des = argv[3];
  // Convierte estos valores a enteros para poder trabajar con ellos
  int origen = atoi(or);
  int destino = atoi(des);
  

  g = leerGrafoNoDirigidoPonderado(archivo);
  mostrar_grafo(g);
  printf("\n");
    
    
  // Realizar el recorrido BFS desde el vértice de origen
  BFS(g, origen);
    
    return 0;
}
*/