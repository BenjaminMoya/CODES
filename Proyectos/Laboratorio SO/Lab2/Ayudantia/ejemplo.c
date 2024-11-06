#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    // El 1 y 2 que se pasa por argumento en exec.c
    int n1 = atoi(argv[1]);
    int n2 = atoi(argv[2]);

    printf("La suma es %d\n", (n1+n2));
    return 0;
}
