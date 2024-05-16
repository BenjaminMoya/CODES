#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define INF 999999

Grafo *crearGrafo(int n, int m){
  Grafo *newGrafo;
  newGrafo = (Grafo *)malloc(sizeof(Grafo));
  newGrafo->n = n;
  newGrafo->m = m;
  newGrafo->Madj = (float **)malloc(sizeof(float *) * n);
  for (int i = 0; i < n; i++) {
    newGrafo->Madj[i] = (float *)malloc(sizeof(float) * n);
  }
  // Inicializar
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      newGrafo->Madj[i][j] = 0;
    }
  }
  return newGrafo;
}

Arista *crearArista(int ver1, int ver2){
  Arista *A;
  A = (Arista *)malloc(sizeof(Arista));
  A->ver1 = ver1;
  A->ver2 = ver2;
  return A;
}

// Grafo No Dirigido Ponderado
Grafo *leerGrafoNoDirigidoPonderado(char *nombreArchivo){
  FILE *fp; // creamos una variable tipo archivo
  fp = fopen(nombreArchivo, "r"); // definimos el tipo de apertura
  int n_vertices, m_aristas; //creamos las variables n y m
  int i, j, k; // i y j serán las coordenadas de la matriz y k es un iterador.
  Grafo *G; // Definimos el grafo
  float w; // w indica el peso de una arista
  if (fp == NULL) {
    printf("Error de archivo\n");
    return NULL;
  } 
  else {
    // Recogemos los datos de vertices y aristas
    if(fscanf(fp, "%d %d", &n_vertices, &m_aristas)){
    G = crearGrafo(n_vertices, m_aristas);
    // dependiendo de las lineas de archivo,
    // 1 para grafo no dirigido no ponderado
    for (k = 0; k < m_aristas; k++) {
      if (fscanf(fp, "%d %d %f", &i, &j, &w)) {
        G->Madj[i][j] = w;
        G->Madj[j][i] = w;
      }
    }
    fclose(fp);
    }
  }
  return G;
}

//simplemente recorremos la matriz completa y mostramos coordenada por coordenada
void mostrar_grafo(Grafo *g) {
  printf("Número de aristas:%d\n", g->m);
  for (int i = 0; i < g->n; i++) {
    for (int j = 0; j < g->n; j++) {
      printf(" %.3f ", g->Madj[i][j]);
    }
    printf("\n");
  }
}

void insertar_arista(Grafo *g, Arista *A, int w){
  g->Madj[A->ver1][A->ver2] = w;
  g->Madj[A->ver2][A->ver1] = w;
  g->m = g->m + 1;
}

//recorremos la mitad superior de la matriz desde la diagonal principal
void mostrar_aristas(Grafo *g) {
  for (int i = 0; i < g->n; i++) {
    for (int j = i; j < g->n; j++) {
      if (g->Madj[i][j] == 1)
        printf(" (%d,%d)", i, j);
    }
  }
}

void obtener_aristas(Grafo *g, Arista aristas[]) {
  // Arista A[g->m];
  Arista a;
  int k = -1;
  for (int x = 0; x < g->n; x++) {
    for (int y = x; y < g->n; y++) {
      if (g->Madj[x][y] != 0) {
        k++;
        a.ver1 = x;
        a.ver2 = y;
        aristas[k] = a;
      }
    }
  }
}

void remover_arista(Grafo *g, Arista *A) {
  g->Madj[A->ver1][A->ver2] = 0;
  g->Madj[A->ver2][A->ver1] = 0;
  g->m = g->m - 1;
}

int pertenece_arista(Grafo *g, Arista *A) {
  if (g->Madj[A->ver1][A->ver2] != 0 && g->Madj[A->ver2][A->ver1] != 0) {
    return 1;
  } 
  else {
    return 0;
  }
}

int pertenece_vertice(Grafo *g, int ver) {
  for (int i = 0; i < g->n; i++) {
    if (i == ver) {
      return 1;
    } 
  }
  return 0;
}

int obtener_grado_vertice(Grafo *g, int i) {
  printf("El grado del vértice |%d| es: \n", i);
  int grado = 0;
  for (int k = 0; k < g->n; k++) {
    if (g->Madj[i][k] != 0)
      grado = grado + 1;
  }
  return grado;
}

void obtener_adyacentes_vertice(Grafo *g, int i) {
  printf("Los vertices adyacentes a |%d| son: \n", i);
  for (int k = 0; k < g->n; k++) {
    if (g->Madj[i][k] == 1)
      printf("|%d| ", k);
  }
}


//----------------------------------------DIJKSTRA A CADA VERTICE--------------------------------------------//

int DistanciaMin(Grafo *G, float distancia[], bool visitados[]) {
  int min = INF;
  int indice = -1;
    
    for (int v = 0; v < G->n; v++) {
      if (!visitados[v] && distancia[v] <= min) {
        min = distancia[v];
        indice = v;
      }
    }
    
  return indice;
}

void dijkstra(Grafo *G, int origen) {
  float distancia[G->n];  // Arreglo de distancias menores
  bool visitados[G->n];  // Arreglo de vertices visitados
    
  for (int i = 0; i < G->n; i++) {
    distancia[i] = INF;
    visitados[i] = false;
  }
    
  distancia[origen] = 0;  // La distancia del origen hacia si mismo es 0
    
  for (int it = 0; it < G->n - 1; it++) {
    int ver = DistanciaMin(G, distancia, visitados);
    visitados[ver] = true;
        
    for (int v = 0; v < G->m; v++) {
      if (!visitados[v] && G->Madj[ver][v] != 0 && distancia[ver] != INF && distancia[ver] + G->Madj[ver][v] < distancia[v]) {
        distancia[v] = distancia[ver] + G->Madj[ver][v];
      }
    }
  }
    
  printf("Vértice | Distancia desde el origen\n");
  for (int i = 0; i < G->n; i++) {
    printf("   %i   |   %.2f\n  ", i, distancia[i]);
  }
}

//----------------------------------------DIJKSTRA A UN VERTICE ESPECÍFICO--------------------------------------------//


void mostrar_ruta(int padres[], int destino) {
  if (padres[destino] == -1) {
    printf("%d ", destino);
    return;
  }

  mostrar_ruta(padres, padres[destino]);
  printf("%d ", destino);
}

void dijkstra_destino(Grafo *G, int origen, int destino) {
  float distancia[G->n];
  int padres[G->n];
  bool visitados[G->n];

  for (int i = 0; i < G->n; i++) {
    distancia[i] = INF;
    visitados[i] = false;
    padres[i] = -1;      
  }

  distancia[origen] = 0;

  for (int it = 0; it < G->n - 1; it++) {
    int ver = DistanciaMin(G, distancia, visitados);
    visitados[ver] = true;

    for (int v = 0; v < G->n; v++) {
      if (!visitados[v] && G->Madj[ver][v] && distancia[ver] != INF && distancia[ver] + G->Madj[ver][v] < distancia[v]) {
        distancia[v] = distancia[ver] + G->Madj[ver][v];
        padres[v] = ver;
      }
    }
  }

  if (distancia[destino] != INF) {
    printf("Distancia más corta desde el vértice %d hasta el vértice %d es : %.2f\n", origen, destino, distancia[destino]);
    printf("La ruta más corta es: ");
    mostrar_ruta(padres, destino);
    printf("\n");
  } 
  else {
    printf("No hay ruta desde el vértice %d hasta el vértice %d\n", origen, destino);
  }
}