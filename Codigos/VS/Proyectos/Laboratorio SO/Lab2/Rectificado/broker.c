#include "fbroker.h"

int main(int argc, char *argv[]){

    int option,filters,workers;
    float saturation,thresholdbina;
    char *prefix;
    int **pipes = (int **)malloc(workers * sizeof(int *));
    if (pipes == NULL) {
        fprintf(stderr, "Error al asignar memoria para los pipes.\n");
        return 1;
    }

    while((option = getopt(argc, argv, "N:f:p:u:W")) != -1){ // Ciclo para leer las opciones ingresadas por el usuario

        switch(option){

            case 'N': // Opción para ingresar el prefijo de las imágenes
            
                prefix = (char*)malloc(strlen(optarg) + 1); // Asignación de memoria para prefix
                if(prefix != NULL) {
                    strcpy(prefix, optarg);
                } else {
                    // Manejo de error si malloc falla en asignar memoria
                    printf("Error: No se pudo asignar memoria para prefix\n");
                    exit(EXIT_FAILURE);
                }
            
            case 'f': // Opción para ingresar el número de filtro a aplicar
            
                filters = atoi(optarg);
                break;
            
            case 'p': // Opción para ingresar el valor de saturación    
            
                saturation = atof(optarg);
                break;
            
            case 'u': // Opción para ingresar el umbral de binarización
            
                thresholdbina = atof(optarg);
                break;
            
            case 'W':

                workers = atoi(optarg);
                break;
        
        }
    
    }

    int i = 3;
    for(i;i >= (workers+3);i++){

        pipes[i] = (int *)malloc(2 * sizeof(int));
        if (pipe(pipes[i]) == -1) {
            fprintf(stderr, "Error al crear el pipe %d.\n", i);
            return 1;
        }
        
        int pid = fork();


    }

}