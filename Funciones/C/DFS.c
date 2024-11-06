#include <stdio.h>
#include <stdbool.h>
#include "grafo.h"


void dfsRecursivo(Grafo* grafo, int vertice, bool visitados[]) {
    visitados[vertice] = true;
    printf("%d ", vertice);

    for (int i = 0; i < grafo->vertices; i++) {
        if (grafo->matrizAdy[vertice][i] == 1 && !visitados[i]) {
            dfsRecursivo(grafo, i, visitados);
        }
    }
}

void dfs(Grafo* grafo, int origen) {
    bool visitados[MAX_VERTICES];

    for (int i = 0; i < grafo->vertices; i++) {
        visitados[i] = false;
    }

    dfsRecursivo(grafo, origen, visitados);
}

int main() {
    int numVertices = 6;
    Grafo grafo;
    
    inicializarGrafo(&grafo, numVertices);
    
    agregarArista(&grafo, 0, 1);
    agregarArista(&grafo, 0, 2);
    agregarArista(&grafo, 1, 3);
    agregarArista(&grafo, 1, 4);
    agregarArista(&grafo, 2, 4);
    agregarArista(&grafo, 3, 4);
    agregarArista(&grafo, 3, 5);
    
    int origen = 0;
    
    DFS(&grafo, origen);
    
    return 0;
}






