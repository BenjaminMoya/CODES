#include<stdio.h>
#include<stdlib.h>
#include<math.h>
//crear la struct
typedef struct lista
{
    int tam;
    int *A;
}lista;
//que funciones tendra
/*
1-crear lista
2-insertar al inicio
3-insertar final
4-buscar elemento
5-primero de la lista
6-ultimo de la lista
7-is vacia
8-is full
9-largo lista
10-insertar elemento
*/
//Creacion de funciones
//1-crear lista
lista *crear(int n){
    //le reservo el espacio necesario para la struct
    lista *l=malloc(sizeof(lista));
    l->tam=n;
    //por que quiero crear un arreglo de enteros por ende el espacio que reserve con mallco debe ser para numeros enteros
    l->A=malloc(sizeof(int)*n); 
    printf("lista creada correctamente\n");
    return l;
}
//2-insertar al inicio
void insertarinicio(int dato,lista *l){
    l->tam++; //aumentamos el tamaño del array ya que agregaremos un nuevo elemento
    l->A=realloc(sizeof(int)*l->tam); //reasignamos el tamaño de la memoria a guardar
    int i;
    for(i=0;i<l->tam;i++){
        l->A[i+1]=l->A[i] //desplazamos los datos a la derecha
    }
    l->A[0]=dato;
    printf("dato agregado al inicio");
}
//3-insertar al final
void insertarfinal(int dato,lista *l){
    l->tam++; //aumento el tamaño del array
    l->A=realloc(sizeof(int)*l->tam); //reasigno la memoria
    l->A[l->tam-1]=dato; //le asigno al ultimo elemento el dato ingresadi
}
//4-buscar elemento
void buscar(lista *l, int dato){
    int i, flag=0;
    for(i=0;i<l->tam;i++){
        if (l->A[i]==dato){
            printf("El elemento esta en la lista");
            flag=1;
        }
    }
    if(flag==0){
        printf("el elemento no esta en la lista");
    }
}
//5-primero de la lista
int primero(lista *l){
    return l->A[0];
}
//6-Ultimos de la lista
int ultimo(lista *l){
    return l->A[l->tam-1];
}
//7-is vacia
void vacia(lista *l){
    if(l->tam==0){
        printf("la lista esta vacia");
    }
}
//8-full este concepto no lo trabajo ya que el concepto de si esta llena o no no se trabaja en listas dinamicas

//9-largo de la lista
int largo(lista *l){
    return l->tam;
}
//10-insertar
void insertar(lista *l,int pos,int dato){
    int i,j;
    l->tam++; //aumento el tamaño del array
    l->A=realloc(sizeof(int)*l->tam); //reasigno la memoria
    for(i=0;i<l->tam;i++){
        if(i==pos){
            for(j=i;j<l->tam;i++){
                l->A[j+1]=l->A[j]

            }
            l->A[i]=dato;
        }
    }
    printf("dato ingresado correctamente");
}
//yera el tda