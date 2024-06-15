#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
    int A = 1;
    int pid;
    int fd[2];
    int fd1[2];

    // PASO A PASO:
    // 1ro -  Se crea el pipe
    if(pipe(fd) == -1){
        // control de error
        return 0;
    }
    if(pipe(fd1) == -1){
        // control de error
        return 0;
    }

    // 2do - Se hace fork
    pid = fork();

    if(pid == 0){
        char buffer[100];
        // 5to - lee el mensaje y se procesa
        close(fd[1]);
        close(fd1[0]);

        read(fd[0], buffer, sizeof(char)*100);

        printf("Soy el hijo y me llego el mensaje: %s\n",buffer);

        strcat(buffer, " Hola padre");

        // 6to - mando el mensaje procesado
        write(fd1[1], buffer, sizeof(char)*100);
    }else{
        char buffer[100] = "Hola hijo";
        char bufferFinal[100];

        // 3ro -  Se cierra las entradas del pipe que no se utilizan
        close(fd[0]);
        close(fd1[1]);

        // 4to - Manda el mensaje
        write(fd[1], buffer, sizeof(char)*100);

        // 7to - Recibe el mensaje del hijo
        read(fd1[0], bufferFinal, sizeof(char)*100);

        printf("Soy el padre y me llego el mensaje: %s\n", bufferFinal);
    }

    return 0;
}