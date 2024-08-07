#include "fworker.h"

int main(int argc, char *argv[]) {
    int option;
    int filters = 0, workers = 0;
    float saturation = 1.0, thresholdbina = 0.5;
    char *prefix = NULL;

    while ((option = getopt(argc, argv, "N:f:p:u:W:")) != -1) { // Ciclo para leer las opciones ingresadas por el usuario
        switch (option) {
            case 'N': // Opción para ingresar el prefijo de las imágenes
                prefix = (char*)malloc(strlen(optarg) + 1); // Asignación de memoria para prefix
                if (prefix != NULL) {
                    strcpy(prefix, optarg);
                } else {
                    // Manejo de error si malloc falla en asignar memoria
                    printf("Error: No se pudo asignar memoria para prefix\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'f': // Opción para ingresar el número de filtro a aplicar
                filters = atoi(optarg);
                break;
            case 'p': // Opción para ingresar el valor de saturación
                saturation = atof(optarg);
                break;
            case 'u': // Opción para ingresar el umbral de binarización
                thresholdbina = atof(optarg);
                break;
            case 'W': // Opción para ingresar el número de trabajadores
                workers = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Uso: %s -N prefix -f filters -p saturation -u thresholdbina -W workers\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Verificar si los argumentos necesarios han sido proporcionados
    if (prefix == NULL || workers <= 0) {
        fprintf(stderr, "Uso: %s -N prefix -f filters -p saturation -u thresholdbina -W workers\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Asignar memoria para los pipes
    int **pipes = (int **)malloc(workers * sizeof(int *));
    if (pipes == NULL) {
        fprintf(stderr, "Error al asignar memoria para los pipes.\n");
        return 1;
    }

    for (int i = 0; i < workers; i++) {
        pipes[i] = (int *)malloc(2 * sizeof(int));
        if (pipes[i] == NULL) {
            fprintf(stderr, "Error al asignar memoria para el pipe %d.\n", i);
            return 1;
        }
        if (pipe(pipes[i]) == -1) {
            fprintf(stderr, "Error al crear el pipe %d.\n", i);
            return 1;
        }

        int pid = fork();
        if (pid == -1) {
            fprintf(stderr, "Error al crear el proceso hijo.\n");
            return 1;
        } else if (pid == 0) { // Proceso hijo
            close(pipes[i][1]); // Cerrar el lado de escritura del pipe en el hijo

            // Leer el nombre del archivo desde el pipe
            char filename[256];
            read(pipes[i][0], filename, sizeof(filename));

            // Procesar la imagen
            BMPImage* image = read_bmp(filename);
            if (image == NULL) {
                fprintf(stderr, "Error al leer el archivo BMP %s\n", filename);
                exit(EXIT_FAILURE);
            }

            if (filters & 0x1) { // Filtro de saturación
                BMPImage* sat_image = saturate_bmp(image, saturation);
                free_bmp(image);
                image = sat_image;
            }

            if (filters & 0x2) { // Filtro de escala de grises
                BMPImage* gray_image = grayscale(image);
                free_bmp(image);
                image = gray_image;
            }

            if (filters & 0x4) { // Filtro de binarización
                BMPImage* bin_image = binarization(image, thresholdbina);
                free_bmp(image);
                image = bin_image;
            }

            // Construir el nombre del archivo de salida
            char output_filename[256];
            snprintf(output_filename, sizeof(output_filename), "%s_output.bmp", prefix);

            // Escribir la imagen BMP resultante
            write_bmp(output_filename, image);
            free_bmp(image);

            close(pipes[i][0]); // Cerrar el lado de lectura del pipe en el hijo
            exit(0);
        } else { // Proceso padre
            close(pipes[i][0]); // Cerrar el lado de lectura del pipe en el padre

            // Construir el nombre del archivo de entrada
            char input_filename[256];
            snprintf(input_filename, sizeof(input_filename), "%s%d.bmp", prefix, i);

            // Escribir el nombre del archivo al pipe
            write(pipes[i][1], input_filename, strlen(input_filename) + 1);
            close(pipes[i][1]); // Cerrar el lado de escritura del pipe en el padre
        }
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 0; i < workers; i++) {
        wait(NULL);
    }

    // Liberar memoria asignada
    for (int i = 0; i < workers; i++) {
        free(pipes[i]);
    }
    free(pipes);
    free(prefix);

    return 0;
}