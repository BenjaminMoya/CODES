#include "broker.h"

int main(int argc, char *argv[])
{
    int option, filters = 0, workers = 0;
    float saturation = 0.0, thresholdbina = 0.0;
    char *prefix = NULL;

    // Procesamiento de argumentos
    while ((option = getopt(argc, argv, "N:f:p:u:W:")) != -1)
    {
        switch (option)
        {
        case 'N': // Prefijo de las imágenes
            prefix = strdup(optarg);
            if (prefix == NULL)
            {
                fprintf(stderr, "Error: No se pudo asignar memoria para prefix\n");
                exit(EXIT_FAILURE);
            }
            break;
        case 'f': // Número de filtro a aplicar
            filters = atoi(optarg);
            break;
        case 'p': // Valor de saturación
            saturation = atof(optarg);
            break;
        case 'u': // Umbral de binarización
            thresholdbina = atof(optarg);
            break;
        case 'W': // Número de workers
            workers = atoi(optarg);
            break;
        default:
            fprintf(stderr, "Uso: %s -N prefix -f filters -p saturation -u thresholdbina -W workers\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Validación de argumentos
    if (prefix == NULL || workers <= 0)
    {
        fprintf(stderr, "Uso: %s -N prefix -f filters -p saturation -u thresholdbina -W workers\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *csvname = "output.csv";
    new_csv(csvname); // Crear el archivo CSV al inicio
    
    // Crear procesos worker a través del broker
    crear_procesos_worker(workers, prefix, filters, saturation, thresholdbina);

    free(prefix); // Liberar memoria asignada

    return 0;
}