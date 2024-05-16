#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "colapila.h"


typedef struct arista {
  int ver1; // arista ini
  int ver2; // arista fin
} Arista;

typedef struct grafo {
  int n; // cantidad de vertices
  int m; // cantidad aristas
  int **Madj;
} Grafo;

Grafo *crearGrafo(int n);
Arista *crearArista(int ver1, int ver2);
void mostrar_grafo(Grafo *g);
void insertar_arista(Grafo *g, Arista *A);
void mostrar_aristas(Grafo *g);
void obtener_aristas(Grafo *g, Arista aristas[]);
void remover_arista(Grafo *g, Arista *A);
int pertenece_arista(Grafo *g, Arista *A); // Boolean 1 = True, 0 = False
int pertenece_vertice(Grafo *g, int v);
int obtener_grado_vertice(Grafo *g, int v);
void obtener_adyacentes_vertice(Grafo *g, int v);

Grafo *leerGrafoNoDirigido(char *nombreArchivo);

void BFS(Grafo *G, int origen);

void DFS(Grafo *G, int origen);
void dfsCamino(Grafo *G, int actual, bool visitados[]);

void BFSDestino(Grafo *G, int origen, int destino);

bool dfsCaminoDestino(Grafo *G, int actual, bool visitados[], int destino, Pila *pila);
void DFSDestino(Grafo* G, int origen, int destino);

bool esConexo(Grafo *G) ;
void mostrarPartesNoConexas(Grafo *G) ;