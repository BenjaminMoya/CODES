#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    // Lista de argumentos
    char* argv[]={"./ejemplo", "1", "2", NULL};
    // Para poder ejecutar debe existir el ejecutable
    execv(argv[0], argv);

    // Como se reemplaza el proceso, el siguiente
    // printf no se muestra
    printf("Despues de ejecutar el execv\n");
    return 0;
}
