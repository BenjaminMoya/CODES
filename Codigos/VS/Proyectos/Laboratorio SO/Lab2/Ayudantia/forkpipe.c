#include <stdio.h>
#include <unistd.h>

int main(){
    int A = 1;
    int pid;
    int fd[2];

    // PASO A PASO:
    // 1ro -  Se crea el pipe
    if(pipe(fd) == -1){
        // control de error
        return 0;
    }

    // 2do - Se hace fork
    pid = fork();

    if(pid == 0){
        char buffer[10];
        // 5to - mismo procedimiento, pero en este caso se lee el mensaje
        close(fd[1]);
        read(fd[0], buffer, sizeof(char)*10);

        printf("Soy el hijo y me llego el mensaje: %s\n",buffer);
    }else{
        char buffer[10] = "Hola hijo";

        // 3ro -  Se cierra las entradas del pipe que no se utilizan
        // en este caso, solo el padre escribe y solo el hijo lee
        close(fd[0]);

        // 4to - Manda el mensaje
        write(fd[1], buffer, sizeof(char)*10);
    }

    return 0;
}