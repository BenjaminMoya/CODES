#include<stdio.h>
#include<stdlib.h>

typedef struct matriz{
    int fila;
    int columna;
    int **A; //aqui reserva dos espacios de memoria distintos;
} matriz;
matriz *crearmatriz(int fila,int columna){
    matriz *matriz=malloc(sizeof(matriz)); //creo un puntero de tipo matriz y reservare el espacio necesario;
    matriz->fila=fila; //del puntero matriz apunto a fila y le doy su contenido;
    matriz->columna=columna; //del puntero matriz apunto a columna y le doy su contenido;
    matriz->A=malloc(sizeof(int*)*fila); //le doy el espacio para el primer arreglo;
    for(int i=0;i<fila;i++){
        matriz->A[i]= malloc(sizeof(int)*columna); //crea la memoria para los arreglos internos;
        for(int j=0;j<columna;j++){
            matriz->A[i][j]=0; //el puntero matriz apunta al arreglo y le da valores;
        }
    }
    return matriz;
}
void agregar(int dato, int fil, int col,matriz *mat){
    if (fil<0 || fil>mat->fila || col<0 || col>mat->columna){
        printf("error, ingrese valores validos\n");
    }
    else{
        mat->A[fil][col]=dato;
        printf("dato agregado correctamente\n");
    }
}
int ver_elemento(matriz *mat,int fil, int col){
    if (fil<0 || fil>mat->fila || col<0 || col>mat->columna){
        printf("error, ingrese valores validos\n");
        return (mat->A[fil][col]);
    }
    else{
        return (mat->A[fil][col]);
    }
}
int cantdfilas(matriz *mat){
    return mat->fila;
}
int cantdcol(matriz *mat){
    return mat->columna;
}
