#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "TDAGrafo_LA_labS8.h"


int main(int argc,  char *argv[]) {

	int numero_vertices,conexiones[23],i=0,j=1;
	FILE *fp;
	fp=fopen("datos_grafo.txt","r");
	if (fp == NULL){
    	printf("No se pudo abrir el archivo.\n");
    	return 1;
    } 
    while (fscanf(fp, "%d", &numero_vertices) != EOF){
    	conexiones[i]=numero_vertices;
    	i+=1;  
    }
    fclose(fp);
    numero_vertices=conexiones[0];
	Grafo *g;
    g = crear_grafo(numero_vertices);
	//mostrar_grafo(g);
	while(j<=22){
		if (conexiones[j]==conexiones[j+1])
			break;
		else{
			agregar_arista(g,conexiones[j],conexiones[j+1]);
		}
		j+=2;
	}
	mostrar_grafo(g);
	return 0;
}