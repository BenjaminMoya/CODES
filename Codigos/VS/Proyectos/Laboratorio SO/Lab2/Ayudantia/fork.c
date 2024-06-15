#include <stdio.h>
#include <unistd.h>

int main(){
    int A = 1;
    int pid;

    pid = fork();

    // Si el pid es 0 significa que es el proceso hijo
    if(pid == 0){
        A = A + 1;
        printf("Soy el hijo, A: %d\n",A);
    }
    // Si el pid es > a 0 significa que es el proceso padre
    else{
        printf("Soy el padre, A: %d\n", A);
    }

    return 0;
}
