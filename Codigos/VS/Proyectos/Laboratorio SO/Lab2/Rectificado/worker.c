#include "fworker.h"

int main(int argc, char *argv[]) {
    int option;
    int filter = 0;
    float saturation = 1.0, thresholdbina = 0.5;

    while ((option = getopt(argc, argv, "f:p:u:")) != -1) { // Ciclo para leer las opciones ingresadas por el usuario
        switch (option) {
            case 'f': // Opción para ingresar el número de filtro a aplicar
                filter = atoi(optarg);
                break;  
            case 'p': // Opción para ingresar el valor de saturación
                saturation = atof(optarg);
                break;
            case 'u': // Opción para ingresar el umbral de binarización
                thresholdbina = atof(optarg);
                break;
            default:
                fprintf(stderr, "Uso: %s -N prefix -f filters -p saturation -u thresholdbina -W workers\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    sem_wait(&mutexWorker);//Esperar a que todos los workers esten listos;
    //Espera a que el broker le envie el trozo de imagen

    //Recibe el trozo de imagen desde el broker

    //Procesamiento

    if(filter == 1){

        //saturate_bmp(image, saturation);
    } 

    if(filter == 2){

        //grayscale(image);
    }

    if(filter == 3){

        //binarization(image, thresholdbina);
    }

    //Envia el trozo de imagen al broker
    return 1;
}