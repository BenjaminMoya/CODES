#include <stdlib.h>
#include <stdio.h>
#include "colapila.h"

//---------------------------------Programación de funciones-----------------------------------//

Nodo *crearNodo(int val){
  Nodo *N;
  N = (Nodo*) malloc(sizeof(Nodo*));
  N->sig = NULL;
  N->info = val;
  return N;
}

//---------------------------------------------------------------------------------------------//


Pila *crearPila(){
  Pila *p;
  p = (Pila*)malloc(sizeof(Pila));
  p->top = NULL;
  return p;
}

int isEmptyP(Pila *P){
  if(P->top == NULL){
    return 1;  //pila vacía
  }else{
    return 0;
  }
}

void push(Pila *P, int val){
    Nodo *N;
    N = crearNodo(val);
    if (!isEmptyP(P)){
      N->sig = P->top;
    }
    P->top = N;
}

int pop(Pila *P){
    int val = 0; //0 valor nulo
    if(!isEmptyP(P)){
      Nodo *aux;
      aux = P->top;
      P->top = aux->sig; //P->tope = P->tope->sig
      aux->sig =NULL;
      val = aux->info;
      free(aux);
    }
    return val;

}

int tope(Pila *P){
  return P->top->info;
}


void destruir_pila(Pila *p){
    while (p->top != NULL)
        pop(p);
}

//-------------------------------------------------------------------------------------------//


Cola *crearCola(){
    Cola *C;
    C = (Cola*) malloc(sizeof(Cola*));
    C->fin = NULL;
    C->frente = NULL;
    return C;
}

int isEmptyC(Cola *C){
    if(C->fin == NULL){
        return 1;
    }
    return 0;
}

void encolar(Cola *C,int val){
    Nodo *N;
    N = crearNodo(val);
    if(isEmptyC(C)){
        C->frente = N;
    }else{
        C->fin->sig = N;
    }
    C->fin = N;
}

int desencolar(Cola *C){
    Nodo *aux;
    if(!isEmptyC(C)){
        aux = C->frente;
        int num = aux->info; //guarda dato a eliminar
        C->frente = aux->sig;
        aux->sig = NULL;
        free(aux);
        return num;
    }else{
        return 0; //0 es cola vacía
    }
}

int frente(Cola *C){
    return C->frente->info;
}

void destruir_cola(Cola *C){
    while (C->frente != NULL)
        desencolar(C);
}