#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct arista {
  int ver1; // arista ini
  int ver2; // arista fin
} Arista;

typedef struct grafo {
  int n; // cantidad de vertices
  int m; // cantidad aristas
  float **Madj;
} Grafo;

Grafo *crearGrafo(int n, int m);
Arista *crearArista(int ver1, int ver2);
void mostrar_grafo(Grafo *g);
void insertar_arista(Grafo *g, Arista *A, int w);
void mostrar_aristas(Grafo *g);
void obtener_aristas(Grafo *g, Arista aristas[]);
void remover_arista(Grafo *g, Arista *A);
int pertenece_arista(Grafo *g, Arista *A); // Boolean 1 = True, 0 = False
int pertenece_vertice(Grafo *g, int v);
int obtener_grado_vertice(Grafo *g, int v);
void obtener_adyacentes_vertice(Grafo *g, int v);

Grafo *leerGrafoNoDirigidoPonderado(char *nombreArchivo);

int DistanciaMin(Grafo *G, float distancia[], bool visitados[]);
void dijkstra(Grafo *G, int origen);
void dijkstra_destino(Grafo *G, int origen, int destino);