#include "fworker.h"

// Función principal
int main(int argc, char* argv[]) {
    int opt;
    const char* input_file = NULL;
    const char* output_file = NULL;
    float factor = 1.0;
    float umbral = 0.5;
    int grayscale_flag = 0;
    int binarization_flag = 0;
    int saturation_flag = 0;

    // Analizar argumentos de línea de comando
    while ((opt = getopt(argc, argv, "i:o:s:g:b:u:")) != -1) {
        switch (opt) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 's':
                saturation_flag = 1;
                factor = atof(optarg);
                break;
            case 'g':
                grayscale_flag = 1;
                break;
            case 'b':
                binarization_flag = 1;
                umbral = atof(optarg);
                break;
            case 'u':
                umbral = atof(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s -i input_file -o output_file [-s factor] [-g] [-b umbral]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (input_file == NULL || output_file == NULL) {
        fprintf(stderr, "Usage: %s -i input_file -o output_file [-s factor] [-g] [-b umbral]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Leer la imagen BMP
    BMPImage* image = read_bmp(input_file);
    if (image == NULL) {
        fprintf(stderr, "Error reading BMP file %s\n", input_file);
        exit(EXIT_FAILURE);
    }

    // Procesar la imagen según las opciones
    if (grayscale_flag) {
        BMPImage* gray_image = grayscale(image);
        free_bmp(image);
        image = gray_image;
    }

    if (binarization_flag) {
        BMPImage* bin_image = binarization(image, umbral);
        free_bmp(image);
        image = bin_image;
    }

    if (saturation_flag) {
        BMPImage* sat_image = saturate_bmp(image, factor);
        free_bmp(image);
        image = sat_image;
    }

    // Escribir la imagen BMP resultante
    write_bmp(output_file, image);

    // Liberar la memoria de la imagen
    free_bmp(image);

    return 0;
}
