#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Nodo{
  int dato;
  struct Nodo *sig;
}Nodo;

typedef struct Lista{
  Nodo *head;
}Lista;

typedef struct Arista{
  int v;
  int w;
}Arista;

typedef struct grafo{
  int n; //Cantidad de vertices
  int m; //Cantidad de aristas
  Lista **Listas;
}Grafo;

/*----------------------------FUNCIONES TDA----------------------------*/

Nodo *crear_nodo(int dato);
Lista *crear_lista();
Grafo *crear_grafo(int n);
Arista *crear_arista();

Grafo *leerGrafoNoDirigido(char *nombreArchivo);

/*-------------------------FUNCIONES LISTA-------------------------*/

int es_vacia(Lista *L);
void insertarNodoI(Lista *L, int dato);
void insertarNodoF(Lista *L, int dato);
void recorrer_lista(Lista *L);
Nodo *buscar_nodo(Lista *L, int dato);
int eliminarNodoI(Lista *L);
int eliminarNodoF(Lista *L);
void eliminarNodo(Lista *L, int dato);

/*-------------------------FUNCIONES GRAFO---------------------------*/

void insertar_arista(Grafo *G,Arista *A);
void remover_arista(Grafo *G,Arista *A);
void mostrar_grafo(Grafo *G);
int pertenece_arista(Grafo *G,Arista *A); // Boolean 1 = True, 0 = False
Arista **obtener_aristas(Grafo *G);
int obtener_grado(Grafo *G, int v);
void *obtener_adyacentes(Grafo *G, int v);
void grado_cada_vertice(Grafo *G, int n);

void es_simple(Grafo *G, int n);
void es_conexo(Grafo *G, int n);


void DFS(Grafo *G, int origen);
void DFSCamino (Grafo *G, int actual, bool visitados[]);

void BFS(Grafo *G, int origen);

void BFSDestino(Grafo *G, int origen, int destino);

void DFSDestino(Grafo *G, int origen, int destino);
bool dfsCaminoDestino(Grafo *G, int actual, bool visitados[], int destino);