#include<stdio.h>
#include<stdlib.h>
#include <math.h>
//definir la struct del TDA
typedef struct punto
{
    float x;
    float y;
} punto;
//que funciones tendra
/*
1-crear punto (punto ya que estoy creando una struct tipo punto)
2-obtener cuadrante (entero o void ya vere)
3-desplazar punto (float)
4-obtener distancia entre dos puntos (float)
*/
//Creacion de funciones

//1-crear punto
punto *crear_punto(float x1,float y1){
    //reservo espacio para el struct tipo punto que contiene x e y
    punto *p=malloc(sizeof(punto)); 
    //le asigno a la variable x de la struct el valor ingresado
    p->x=x1; 
    //le asigno a la variable y de la struct el valor ingresado
    p->y=y1; 
    printf("punto creado correctamente\n");
    //retorno el struct punto con los valores ingresados
    return p;
}
//2-obtener cuadrantes
void cuadrante(punto *p){
    float x,y;
    x=p->x;
    y=p->y;
    if(x>=0){
        if(y>=0){
            printf("esta en el cuadrante ++");
        }
        else{
            printf("esta en el cuadrante +-");
        }
    }
    else{
        if(y>=0){
            printf("esta en el cuadrante -+");
        }
        else{
            printf("esta en el cuadrante --");
        }
    }
}
//3-imprimirpunto
bool mostrar_punto(punto *p)
{
    printf("\n(%f,%f)",p->x,p->y);
    return true;
}
//4-desplzamiento
punto *desplazar_punto(int eje_x,int eje_y,punto *p)
{
    p->x=p->x+eje_x;
    p->y=p->y+eje_y;
    return p;
}
//5-distancia
float distancia(punto *p1,punto *p2);
{
    float x1,x2,y1,y2,distancia;
    x1=p1->x;
    x2=p2->x;
    y1=p1->y;
    y2=p2->y;
    distancia=sqrt(pow((x1+x2),2)+pow((y1+y2),2));
    return distancia;
}
//6-punto medio
punto *punto_medio(punto *p1, punto *p2)
{
    int *nuevopunto;
    float x1,x2,y1,y2,medio_x,medio_y;
    x1=p1->x;
    x2=p2->x;
    y1=p1->y;
    y2=p2->y;
    medio_x=(x1+x2)/2;
    medio_y=(y1+y2)/2;
    nuevopunto=crear_punto(medio_x,medio_y);
    return nuevopunto;
}