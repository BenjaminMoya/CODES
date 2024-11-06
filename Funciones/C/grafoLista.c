#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Nodo *crear_nodo(int dato) {
  Nodo *nodo;
  nodo = (Nodo *)malloc(sizeof(Nodo));
  nodo->dato = dato;
  nodo->sig = NULL;
  return nodo;
}

Lista *crear_lista() {
  Lista *L;
  L = (Lista *)malloc(sizeof(Lista));
  L->head = NULL;
  return L;
}

Grafo *crear_grafo(int n) {
  Grafo *G;
  G = (Grafo *)malloc(sizeof(Grafo));
  G->Listas = (Lista **)malloc(sizeof(Lista *) * n);
  G->n = n;
  G->m = 0;
  for (int i = 0; i < n; i++) {
    G->Listas[i] = crear_lista();
  }
  return G;
}


Arista *crear_arista(int v, int w) {
  Arista *A;
  A = malloc(sizeof(Arista));
  A->v = v;
  A->w = w;
  return A;
}

//Leer grafo No Dirigido con Lista de Adyacencia 
Grafo *leerGrafoNoDirigido(char *nombreArchivo){
  FILE *fp;               
  fp = fopen(nombreArchivo,"r");
  int n_vertices, m_aristas;
  int i,j,k;
  
  if (fp ==NULL){
    printf("Error de archivo\n");
    return NULL;
  }
  else{
    Grafo *G;
    //Cantidad de nodos y aristas
    if (fscanf(fp, "%d %d", &n_vertices, &m_aristas)){
      G = crear_grafo(n_vertices);  
      G->n = n_vertices;
      G->m = m_aristas;
      //Creamos e insertamos las aristas al grafo
      for (k = 0; k < m_aristas; k++){
       if (fscanf(fp,"%d %d",&i, &j)){
        Arista *A;
        A = crear_arista(i, j);
        insertar_arista(G, A);
        }
      }
    }
    fclose(fp);
    return G; 
  }
}


/*-------------------------FUNCIONES LISTA-------------------------*/
int es_vacia(Lista *L) {
  if (L->head == NULL) {
    return 1; // Indica verdadero
  } else {
    return 0; // Indica falso
  }
}

void insertarNodoI(Lista *L, int dato) {
  Nodo *nodo;
  nodo = crear_nodo(dato);
  if (es_vacia(L) == 1) {
    L->head = nodo;
  } else {
    nodo->sig = L->head;
    L->head = nodo;
  }
}

void insertarNodoF(Lista *L, int dato) {
  Nodo *nodo;
  nodo = crear_nodo(dato);
  if (es_vacia(L) == 1) {
    L->head = nodo;
  } else {
    Nodo *aux;
    aux = L->head;
    while (aux->sig != NULL) {
      aux = aux->sig;
    }
    aux->sig = nodo;
  }
}

void recorrer_lista(Lista *L) {
  if (es_vacia(L) == 1) {
    printf(" ");
  } else {
    Nodo *aux;
    aux = L->head;
    while (aux != NULL) {
      printf("|%d| ", aux->dato);
      aux = aux->sig;
    }
  }
}

Nodo *buscar_nodo(Lista *L, int dato) {
  if (es_vacia(L) == 1) {
    return NULL;
  } else {
    Nodo *aux;
    aux = L->head;
    while (aux != NULL) {
      if (aux->dato == dato) {
        return aux;
      } else {
        aux = aux->sig;
      }
    }
    return NULL;
  }
}

int eliminarNodoI(Lista *L) {
  int eliminado;
  if (es_vacia(L) == 0) {
    Nodo *aux;
    aux = L->head;
    L->head = L->head->sig;
    aux->sig = NULL;
    eliminado = aux->dato;
    free(aux);
  }
  return eliminado;
}

int eliminarNodoF(Lista *L) {
  int eliminado;
  if (es_vacia(L) == 0) {
    if (L->head->sig == NULL) {
      eliminado = L->head->dato;
      free(L->head);
    } else {
      Nodo *aux, *aux2;
      aux = L->head;
      while (aux->sig->sig != NULL) {
        aux = aux->sig;
      }
      aux2 = aux->sig;
      aux->sig = NULL;
      eliminado = aux2->dato;
      free(aux2);
    }
  }
  return eliminado;
}

void eliminarNodo(Lista *L, int dato) {
  if (es_vacia(L) != 0) {
    Nodo *aux, *aux2;
    aux = L->head;
    while (aux != NULL) {
      if (aux->dato == dato) {
        if (aux == L->head) {
          L->head = aux->sig;
          free(aux);
        } else {
          aux2->sig = aux->sig;
          free(aux);
        }
      } else {
        aux2 = aux;
        aux = aux->sig;
      }
    }
  }
}

/*-------------------------FUNCIONES GRAFO---------------------------*/

void insertar_arista(Grafo *G, Arista *A) {
  if (buscar_nodo(G->Listas[A->v], A->w) != NULL) {
    printf("La arista ya pertenece al grafo\n");
  } else {
    Nodo *nodo;
    nodo = crear_nodo(A->w);
    insertarNodoI(G->Listas[A->v], A->w);
    nodo = crear_nodo(A->v);
    insertarNodoI(G->Listas[A->w], A->v);
    G->m++;
  }
}

void remover_arista(Grafo *G, Arista *A) {
  Nodo *nodo;
  nodo = (buscar_nodo(G->Listas[A->v], A->w));
  if (nodo == NULL) {
    printf("La arista no pertenece al grafo\n");
  } else {
    eliminarNodo(G->Listas[A->v], A->w);
    eliminarNodo(G->Listas[A->w], A->v);
    G->m--;
  }
}

void mostrar_grafo(Grafo *G) {
  for (int i = 0; i < G->n; i++) {
    printf("|%d| -> ", i);
    recorrer_lista(G->Listas[i]);
    printf("\n");
  }
}

int pertenece_arista(Grafo *G, Arista *A) {
  if (buscar_nodo(G->Listas[A->v], A->w) != NULL) {
    return 1; // Verdadero
  } else {
    return 0; // Falso
  }
}


Arista **obtener_aristas(Grafo *G) {
  Arista **aristas, *arista;
  aristas = (Arista **)malloc(sizeof(Arista *) * G->m);
  Nodo *aux;
  int pos = 0;
  for (int i = 0; i < G->n; i++) {
    aux = G->Listas[i]->head;
    while (aux != NULL) {
      if (i < aux->dato) {
        arista = crear_arista(i, aux->dato);
        aristas[pos] = arista;
        pos++;
      }
      aux = aux->sig;
    }
  }
  return aristas;
}


int obtener_grado(Grafo *G, int v) {
  Nodo *aux;
  int grado = 0;
  aux = G->Listas[v]->head;
  while (aux != NULL) {
    grado++;
    aux = aux->sig;
  }
  free(aux);
  return grado;
}

void *obtener_adyacentes(Grafo *G, int v) {
  Nodo *aux;
  int adyacente;
  aux = G->Listas[v]->head;
  while (aux != NULL) {
    adyacente = aux->dato;
    printf(" |%d| ", adyacente);
  }
  free(aux);
}

void grado_cada_vertice(Grafo *G, int n) {
  for (int i = 0; i < n; i++) {
    int grado = obtener_grado(G, i);
    printf("El grado del vértice %d es: %d \n", i, grado);
  }
}


//Como el grafo es no dirigido, se considera solo 1 arista entre (a,b) y (b,a), por tanto para que el grafo no sea simple, debería tener bucles.
void es_simple(Grafo *G, int n) {
  int i = 0;
  while (i < n){
    Arista *arista;
    arista = crear_arista(i,i);
    if (pertenece_arista(G,arista) == 1){
      printf("El grafo no es simple");
    }
    else{
      i++;
    }
  }
  printf("El grafo es simple");
}

//------------------------------------Recorrido BFS-----------------------------------//

void BFS(Grafo *G, int origen) {
  bool visitados[G->n];
  int cola[G->n];
  int frente = 0;
  int fin = 0;
    
  for (int i = 0; i < G->n; i++) {
    visitados[i] = false;
  }
    
  visitados[origen] = true;
  cola[fin] = origen;
  fin++;
    
  printf("Recorrido BFS desde el vértice %d: \n", origen);
    
  while (frente != fin) {
    int actual = cola[frente];
    frente++;
    if (frente != 1) {  //este if es solo para que la flecha esté entre cada vertice
      printf("->");
      }
    printf(" %d ", actual);
        
    Nodo *nodo = G->Listas[actual]->head;
    while (nodo != NULL) {
      int vertice = nodo->dato;
      if (!visitados[vertice]) {
        visitados[vertice] = true;
        cola[fin] = vertice;
        fin++;
      }
      nodo = nodo->sig;
    }
  }
  printf("\n");
}

//------------------------------------BFS a un destino-----------------------------------//

void BFSDestino(Grafo* G, int origen, int destino) {
  bool visitados[G->n];
  int cola[G->n];
  int frente = 0;
  int final = 0;

  for (int i = 0; i < G->n; i++) {
    visitados[i] = false;
  }

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
      printf(" %d", actual);
      break;
    }

    printf(" %d ->", actual);

    Nodo* nodo = G->Listas[actual]->head;
    while (nodo != NULL) {
      int adyacente = nodo->dato;
      if (!visitados[adyacente]) {
        visitados[adyacente] = true;
        cola[final] = adyacente;
        final++;
      }
      nodo = nodo->sig;
    }
  }

  if (!encontrado) {
    printf("No se encontró un camino al vértice %d.", destino);
  }

    printf("\n");
}

//------------------------------------Recorrido DFS-----------------------------------//

void DFSCamino (Grafo *G, int actual, bool visitados[]) {
  visitados[actual] = true;
  printf(" %d ", actual);

  Nodo *nodo = G->Listas[actual]->head;
  while (nodo != NULL) {
    int vertice = nodo->dato; //dato sería el vértice
    if (!visitados[vertice]) {
      printf("->");
      DFSCamino(G, vertice, visitados);
    }
    nodo = nodo->sig;
  }
}

void DFS(Grafo *G, int origen) {
  bool visitados[G->n];
    
  for (int i = 0; i < G->n; i++) {
    visitados[i] = false;
  }
    
  printf("Recorrido DFS desde el vértice %d: \n", origen);
  DFSCamino(G, origen, visitados);
  printf("\n");
}

//------------------------------------DFS a un destino-----------------------------------//

bool dfsCaminoDestino(Grafo *G, int actual, bool visitados[], int destino) {
  visitados[actual] = true;
  printf(" %d ", actual);
    
  if (actual == destino) {
    return true;
  }
    
  Nodo *nodo = G->Listas[actual]->head;
  while (nodo != NULL) {
    int vertice = nodo->dato;
    if (!visitados[vertice]) {
      printf("->");
      if (dfsCaminoDestino(G, vertice, visitados, destino)) {
        return true;
      }
    }
    nodo = nodo->sig;
  }  
  
  return false;
}

void DFSDestino(Grafo *G, int origen, int destino) {
  bool visitados[G->n];
    
  for (int i = 0; i < G->n; i++) {
    visitados[i] = false;
  }
    
  printf("Recorrido DFS desde el vértice %d hasta el vértice %d: \n", origen, destino);
  if (dfsCaminoDestino(G, origen, visitados, destino)) {
    printf("\n");
  } 
  else {
    printf("No se encontró un camino.\n");
  }
}