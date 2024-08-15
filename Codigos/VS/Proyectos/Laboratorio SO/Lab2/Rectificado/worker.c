#include "fworker.h"

int main(int argc, char *argv[]) {
    printf("Worker\n");
    int filter_opt = atoi(argv[1]);
    float saturation_fact = atof(argv[2]);
    float threshold_bina = atof(argv[3]);
    
    BMPImage *image_read = (BMPImage*)malloc(sizeof(BMPImage));
    if (image_read == NULL) {
        perror("Error al asignar memoria para BMPImage");
        exit(EXIT_FAILURE);
    }
    printf("Worker leyendo imagen\n");
    // Leer el encabezado de la imagen
    read(STDIN_FILENO, &image_read->width, sizeof(int));
    read(STDIN_FILENO, &image_read->height, sizeof(int));
    read(STDIN_FILENO, &image_read->type, sizeof(int));

    // Reservar memoria para los píxeles
    size_t pixel_data_size = image_read->width * image_read->height * sizeof(RGBPixel);
    image_read->data = (RGBPixel *)malloc(pixel_data_size);
    if (image_read->data == NULL) {
        perror("Error al asignar memoria para los píxeles");
        free(image_read);
        exit(EXIT_FAILURE);
    }

    // Leer los píxeles de la imagen
    read(STDIN_FILENO, image_read->data, pixel_data_size);

    // Aplicar el filtro correspondiente
    if (filter_opt == 1) {
        image_read = saturate_bmp(image_read, saturation_fact);
    } else if (filter_opt == 2) {
        image_read = grayscale(image_read);
    } else if (filter_opt == 3) {
        image_read = binarization(image_read, threshold_bina);
    }
    printf("Worker escribiendo imagen\n");
    // Escribir el encabezado de la imagen procesada
    write(STDOUT_FILENO, &image_read->width, sizeof(int));
    write(STDOUT_FILENO, &image_read->height, sizeof(int));
    write(STDOUT_FILENO, &image_read->type, sizeof(int));

    // Escribir los píxeles de la imagen procesada
    pixel_data_size = image_read->width * image_read->height * sizeof(RGBPixel);
    write(STDOUT_FILENO, image_read->data, pixel_data_size);
    printf("Worker terminado\n");
    // Liberar memoria
    free_bmp(image_read);

    return 0;
}