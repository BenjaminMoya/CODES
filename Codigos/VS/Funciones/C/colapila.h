#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
  int info;
  struct nodo *sig;
}Nodo;

typedef struct pila{
  Nodo *top;
}Pila;

typedef struct cola{
  Nodo *frente;
  Nodo *fin;
}Cola;

//---------Funciones crear Nodo----------//
Nodo *crearNodo(int val);

//---------Funciones Pila----------//
Pila *crearPila();
int isEmptyP(Pila *P);
void push(Pila *P, int val);
int pop(Pila *P);
int tope(Pila *P); //retorna el valor del tope
void destruir_pila(Pila *p);

//--------Funciones Cola----------//
Cola *crearCola();
int isEmptyC(Cola *C);
void encolar(Cola *C, int val);
int desencolar(Cola *C);
int frente(Cola *C); //retorna el valor del frente
void destruir_cola(Cola *C);
