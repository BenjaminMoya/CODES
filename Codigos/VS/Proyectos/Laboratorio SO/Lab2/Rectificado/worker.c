#include "fworker.h"

int main(int argc, char *argv[]) {

    
    int filter_opt = atoi(argv[1]);
    float saturation_fact = atof(argv[2]);
    float threshold_bina = atof(argv[3]);

    BMPImage *image_read = (BMPImage*)malloc(sizeof(BMPImage));
    read(STDIN_FILENO, &image_read->width, sizeof(int));
    read(STDIN_FILENO, &image_read->height, sizeof(int));
    read(STDIN_FILENO, &image_read->type, sizeof(int));

    // Reservar memoria para los píxeles
    size_t pixel_data_size = image_read->width * image_read->height * sizeof(RGBPixel);
    image_read->data = (RGBPixel*)malloc(pixel_data_size);

    // Leer los píxeles de la imagen
    read(STDIN_FILENO, image_read->data, pixel_data_size);
    close(STDIN_FILENO);    

    if(filter_opt == 1){

        image_read = saturate_bmp(image_read, saturation_fact);
    } 

    if(filter_opt == 2){

        image_read = grayscale(image_read);
    }

    if(filter_opt == 3){

        image_read = binarization(image_read, threshold_bina);
    }

    // Enviar los píxeles de la imagen procesada

    pixel_data_size = image_read->width * image_read->height * sizeof(RGBPixel);
    write(STDOUT_FILENO, image_read->data, pixel_data_size);
    close(STDOUT_FILENO);

    free_bmp(image_read);
    exit(EXIT_SUCCESS);
    return 0;
}