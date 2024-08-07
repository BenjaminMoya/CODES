#include "broker.h"

void crear_procesos_worker(int workers, char* prefix, int filters, float saturation, float thresholdbina) {
    int **pipes = (int **)malloc(workers * sizeof(int *));
    if (pipes == NULL) {
        fprintf(stderr, "Error al asignar memoria para los pipes.\n");
        exit(EXIT_FAILURE);
    }

    const char *csvname = "output.csv";

    for (int i = 0; i < workers; i++) {
        pipes[i] = (int *)malloc(2 * sizeof(int));
        if (pipes[i] == NULL) {
            fprintf(stderr, "Error al asignar memoria para el pipe %d.\n", i);
            exit(EXIT_FAILURE);
        }
        if (pipe(pipes[i]) == -1) {
            fprintf(stderr, "Error al crear el pipe %d.\n", i);
            exit(EXIT_FAILURE);
        }

        int pid = fork();
        if (pid == -1) {
            fprintf(stderr, "Error al crear el proceso worker.\n");
            exit(EXIT_FAILURE);
        } else if (pid == 0) { // Proceso hijo - worker
            close(pipes[i][1]); // Cerrar el lado de escritura del pipe en el hijo
            dup2(pipes[i][0], STDIN_FILENO); // Duplicar el descriptor de lectura al stdin
            close(pipes[i][0]); // Cerrar el descriptor original despuÃ©s de duplicarlo

            execl("./worker", "worker", (char *)NULL);
            fprintf(stderr, "Error al ejecutar worker\n");
            exit(EXIT_FAILURE);
        } else { // Proceso padre - broker
            close(pipes[i][0]); // Cerrar el lado de lectura del pipe en el padre

            char input_filename[256];
            snprintf(input_filename, sizeof(input_filename), "%s%d.bmp", prefix, i);

            // Escribir los argumentos al pipe
            dprintf(pipes[i][1], "%s\n%d\n%f\n%f\n%s\n", input_filename, filters, saturation, thresholdbina, csvname);
            close(pipes[i][1]); // Cerrar el lado de escritura del pipe en el padre
        }
    }

    for (int i = 0; i < workers; i++) {
        wait(NULL);
    }

    for (int i = 0; i < workers; i++) {
        free(pipes[i]);
    }
    free(pipes);
}