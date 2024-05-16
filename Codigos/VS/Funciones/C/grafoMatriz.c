#include "grafo.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Grafo *crearGrafo(int n){
  Grafo *newGrafo;
  newGrafo = (Grafo *)malloc(sizeof(Grafo));
  newGrafo->n = n;
  newGrafo->m = 0;
  newGrafo->Madj = (int **)malloc(sizeof(int *) * n);
  for (int i = 0; i < n; i++) {
    newGrafo->Madj[i] = (int *)malloc(sizeof(int) * n);
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

// Grafo No Dirigido
Grafo *leerGrafoNoDirigido(char *nombreArchivo) {
  Grafo *G;
  Arista *A;
  int n_vertices;
  int i, j, k;
  FILE *fp = fopen(nombreArchivo, "r");
  if (fp == NULL) {
    printf("Error al abrir el archivo.\n");
    return NULL;
  }
  else{
    // Leer el número de vértices
    if(fscanf(fp, "%d", &n_vertices)){ //este if es solo para evitar warnings
    G = crearGrafo(n_vertices);
    }
    
    // Leer las conexiones entre los vértices desde el archivo
    while (fscanf(fp, "%d %d", &i, &j) != EOF) {
      A = crearArista(i,j);
      insertar_arista(G, A);
    }
    
    fclose(fp);
    
    return G;
  }
}

//simplemente recorremos la matriz completa y mostramos coordenada por coordenada
void mostrar_grafo(Grafo *g) {
  printf("Número de aristas:%d\n", g->m);
  for (int i = 0; i < g->n; i++) {
    for (int j = 0; j < g->n; j++) {
      printf(" %d ", g->Madj[i][j]);
    }
    printf("\n");
  }
}

void insertar_arista(Grafo *g, Arista *A){
  g->Madj[A->ver1][A->ver2] = 1;
  g->Madj[A->ver2][A->ver1] = 1;
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
    if (g->Madj[i][k] == 1){
      printf("|%d| ", k);
    }
  }
}

//----------------------------------------RECORRIDO BFS--------------------------------------------//

// Función para realizar el recorrido BFS con matriz de adyacencia
void BFS(Grafo *G, int origen) {
  bool visitados[G->n]; //arreglo de tipo booleano para marcar los visitados
  int cola[G->n]; //arreglo para llevar el orden de los vertices visitados
  int frente = 0; //nos ayudará a desencolar
  int final = 0; //nos ayudará a encolar

  for (int i = 0; i < G->n; i++) {  //inicializamos los visitados todos en false
    visitados[i] = false;
  }
  
  // Marcamos el vértice de origen como visitado y encolarlo
  visitados[origen] = true;
  cola[final] = origen;
  final++;

  printf("Recorrido BFS desde el vértice %d : ", origen);

  while (frente != final) { //equivalente a preguntar si la cola no es vacía
    int actual = cola[frente];  //iniciamos tomando el vertice que primero esté en la cola
    frente++;
    printf("%d ", actual); //mostramos el vertice recién desencolado

    // Recorremos los vértices adyacentes al vértice actual
    for (int i = 0; i < G->n; i++) {
      if (!visitados[i] && G->Madj[actual][i] == 1) { //El vertice no debe estar visitado y debe existir la arista 
        visitados[i] = true; // Lo marcamos como visitado
        cola[final] = i;  // Lo encolamos
        final++;
      }
    }
  }
  printf("\n");
}

//-------------------------------BFS A VERTICE ESPECIFICO-----------------------------------//

void BFSDestino(Grafo *G, int origen, int destino) {
  bool visitados[G->n];
  int cola[G->n];
  int frente = 0;
  int final = 0;

  for (int i = 0; i < G->n; i++) {
    visitados[i] = false;
  }
  
  // Marcar el vértice de origen como visitado y encolarlo
  visitados[origen] = true;
  cola[final] = origen;
  final++;

  printf("Recorrido BFS desde el vértice %d hasta el vértice %d: \n", origen, destino);

  bool encontrado = false;

  while (frente != final) {
    int actual = cola[frente];
    frente++;

    if (actual == destino) {
      encontrado = true;
      printf("%d ", actual);
      break;
    }

    printf("%d -> ", actual);

    // Recorrer los vértices adyacentes al vértice actual
    for (int i = 0; i < G->n; i++) {
      if (!visitados[i] && G->Madj[actual][i] == 1) {
        visitados[i] = true;
        cola[final] = i;
        final++;
      }
    }
  }

  if (!encontrado) {
    printf("No se encontró un camino al vértice %d.", destino);
  }

  printf("\n");
}


//----------------------------------------RECORRIDO DFS--------------------------------------------//

void dfsCamino(Grafo *G, int actual, bool visitados[]) {
  visitados[actual] = true;
  printf("%d ", actual);

  for (int i = 0; i < G->n; i++) {
    if (!visitados[i] && G->Madj[actual][i] == 1) {
      dfsCamino(G, i, visitados);
    }
  }
}

void DFS(Grafo *G, int origen) {
  bool visitados[G->n];
  for (int i = 0; i < G->n; i++) {
    visitados[i] = false;
  }
  printf("Recorrido DFS desde el vértice %d : ",origen);
  dfsCamino(G, origen, visitados);
  printf("\n");
}


//---------------------------------DFS A VERTICE ESPECIFICO-----------------------------------//

bool dfsCaminoDestino(Grafo *G, int actual, bool visitados[], int destino, Pila *pila) {
  visitados[actual] = true;

  if (actual == destino) {
    push(pila, actual);
    return true;
  }

  for (int i = 0; i < G->n; i++) {
    if (!visitados[i] && G->Madj[actual][i] == 1) {
      if (dfsCaminoDestino(G, i, visitados, destino, pila)) {
        push(pila, actual);
        return true;
      }
    }
  }

  // Si no se encontró el destino, desapilar el elemento actual
  pop(pila);
  return false;
}


void DFSDestino(Grafo *G, int origen, int destino) {
  bool visitados[G->n];
  for (int i = 0; i < G->n; i++) {
    visitados[i] = false;
  }

  Pila *pila = crearPila();

  printf("Recorrido DFS desde el vértice %d hasta el vertice %d:\n", origen, destino);
  if (dfsCaminoDestino(G, origen, visitados, destino, pila)) {
    // Mostrar el camino desde la pila en orden inverso
    while (!isEmptyP(pila)) {
      printf("%d ", pop(pila));
      if (!isEmptyP(pila)) {
        printf("-> ");
      }
    }
    printf("\n");
  } 
  else {
    printf("No hay un camino posible :(\n");
  }
}