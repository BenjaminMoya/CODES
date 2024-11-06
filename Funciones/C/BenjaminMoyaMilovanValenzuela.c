#include <stdio.h>

/* Se definen los parametros en los que estan limitadas variables, donde n que representa la cantidad de misiones, v es el numero necesario de XPs para subir de nivel, c es el multiplicador de XP,
x que es la cantidad de experiencia necesaria para subir en relacion a cada nivel ingresado y d es el nivel recomendado para i mision */

#define MAX_N 2000
#define MIN_N 1
int n, v, c;
int x[MAX_N];
int d[MAX_N];
int maxXP = 0;

/*Para el backtracking tomamos 2 parametros, la etapa actual en que estamos y la experiencia acumulada actual */
void backtracking(int nivel, int xp_actual) {
    /*Si la etapa calza con el numero de misiones, significa que se realizaron todas las misiones, por lo que si el nivel actual es mayor a la experiencia acumulada, reemplazaremos
    este valor y se cerrara el retroceso*/
    if (nivel == n) {
        if (xp_actual > maxXP) {
            maxXP = xp_actual;
        }
        return;
    }

    /* Si solo hay niveles mayores o iguales que lo recomendado, completaremos la misión sin bonificación, sumandole al contador de XPs lo que se indique previamente */

    if (xp_actual >= d[nivel]) {
        backtracking(nivel + 1, xp_actual + x[nivel]);
    }

    /* Si el nivel actual es menor que lo recomendado, completaremos la misión con bonificación, sumandole al contador de XPs lo que se indique previamente con el multiplicador asociado en un principio */

    if (xp_actual < d[nivel]) {
        backtracking(nivel + 1, xp_actual + c * x[nivel]);
    }
}

int main(){
    printf("Numero de misiones, Experiencia necesaria para subir de nivel, Multiplicador de dificultad:");
    scanf("%d %d %d", &n, &v, &c);
    for (int i = 0; i < n; i++) {
        printf("Experiencia otorgada por el nivel y nivel recomendado para la mision %d:",i);
        scanf("%d %d", &x[i], &d[i]);
    }

    /* Se comienza la evaluacion de caminos hasta que nos arroje el maxXP mayor */ 
    backtracking(0, 0);

    return 0;
}