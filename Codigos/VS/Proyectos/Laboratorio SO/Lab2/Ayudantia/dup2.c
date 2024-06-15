#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    // Se crea un pipe para escribir en él
    int fd[2];
    pipe(fd);

    // Se duplica STD_OUT y se le asigna fd[1]
    dup2(STDOUT_FILENO, fd[1]);

    // Como se asignó fd[1] a STD_OUT, al momento de escribir en
    // el pipe, el mensaje debería mostrarse por terminal
    char buffer[100] = "Mensaje escrito por el pipe\n";
    write(fd[1], buffer, 100);
    return 0;
}