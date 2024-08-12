#include "fworker.h"

int main(int argc, char *argv[]) {

    sem_t *mutex_broker = sem_open("/mutex_broker", 0); // No se crea, solo se abre
    if (mutex_broker == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    sem_t *mutex_worker = sem_open("/mutex_worker", 0); // No se crea, solo se abre
    if (mutex_worker== SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }
    
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

    sem_wait(mutex_worker); 

    //Recibe el trozo de imagen desde el broker

    BMPImage* image_read;
    ssize_t bytes_read = read(STDIN_FILENO, image_read, sizeof(image_read));
    if (bytes_read != sizeof(image_read)) {
        perror("read");
        exit(EXIT_FAILURE);
    }

        // Leer los datos de la imagen
    image_read->data = malloc(image_read->width * image_read->height * sizeof(RGBPixel));
    if (image_read->data == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    bytes_read = read(STDIN_FILENO, image_read->data, image_read->width * image_read->height * sizeof(RGBPixel));
    if (bytes_read != image_read->width * image_read->height * sizeof(RGBPixel)) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    if(filter == 1){

        image_read = saturate_bmp(image_read, saturation);
    } 

    if(filter == 2){

        image_read = grayscale(image_read);
    }

    if(filter == 3){

        image_read = binarization(image_read, thresholdbina);
    }
    
    ssize_t bytes_written = write(STDOUT_FILENO, image_read, sizeof(image_read));
    if (bytes_written != sizeof(image_read)) {
        perror("write");
        exit(EXIT_FAILURE);
    }
    bytes_written = write(STDOUT_FILENO, image_read->data, image_read->width * image_read->height * sizeof(RGBPixel));
    if (bytes_written != image_read->width * image_read->height * sizeof(RGBPixel)) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    free(image_read->data);
    exit(EXIT_SUCCESS);
    sem_post(mutex_broker);
    return 1;
}