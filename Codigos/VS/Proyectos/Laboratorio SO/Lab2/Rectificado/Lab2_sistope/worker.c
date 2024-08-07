#include "worker.h"
void aplicar_filtros_y_guardar(const char* filename, int filters, float saturation, float thresholdbina, const char* csvname) {
    BMPImage* image = read_bmp(filename);
    if (image == NULL) {
        fprintf(stderr, "Error al leer el archivo BMP %s\n", filename);
        exit(EXIT_FAILURE);
    }

    if (filters & 0x1) {
        BMPImage* sat_image = saturate_bmp(image, saturation);
        free_bmp(image);
        image = sat_image;
    }

    if (filters & 0x2) {
        BMPImage* gray_image = grayscale(image);
        free_bmp(image);
        image = gray_image;
    }

    if (filters & 0x4) {
        BMPImage* bin_image = binarization(image, thresholdbina);
        free_bmp(image);
        image = bin_image;
    }

    char output_filename[256];
    snprintf(output_filename, sizeof(output_filename), "%s_output.bmp", filename);

    write_bmp(output_filename, image);

    // Actualizar el nombre y tipo en la estructura para el CSV
    image->name = strdup(output_filename);
    image->type = (filters & 0x4) ? 1 : 0;
    write_csv(image, csvname);

    free_bmp(image);
}

int main() {
    char filename[256];
    int filters;
    float saturation, thresholdbina;
    char csvname[256];

    if (scanf("%255s %d %f %f %255s", filename, &filters, &saturation, &thresholdbina, csvname) != 5) {
        fprintf(stderr, "Error al leer los argumentos del broker\n");
        exit(EXIT_FAILURE);
    }

    aplicar_filtros_y_guardar(filename, filters, saturation, thresholdbina, csvname);

    return 0;
}