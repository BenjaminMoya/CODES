#include <stdio.h>

//Funcion que verifica el mayor entre 2 numero, si es verdadera retorna el primero, 
//si es falsa retorna el segundo. Se podria hacer dentro de la funcion principal, pero es mas sencillo perderse en 
//los condicionales sin esta.
int mayor(int a, int b) {
    return (a > b) ? a : b;
}

int maxima_cantidad_de_piezas(int n, int a, int b, int c) {
    // Crear un arreglo combinaciones para almacenar la cantidad máxima de piezas de cinta
    // que se pueden obtener para cada longitud de cinta desde 0 hasta n
    int combinaciones[n + 1];

    // El valor inicial de combinaciones[0] es 0, ya que no hay ninguna cinta para cortar
    combinaciones[0] = 0;

    // Calcular la cantidad máxima de piezas de cinta para cada longitud desde 1 hasta n
    for (int i = 1; i <= n; i++) {
        // Inicializar combinaciones[i] como -1 para indicar que aún no se ha encontrado una solución
        combinaciones[i] = -1;

        // Comprobar si es posible obtener una pieza de longitud a
        if (i - a >= 0)
            combinaciones[i] = mayor(combinaciones[i], combinaciones[i - a]);

        // Comprobar si es posible obtener una pieza de longitud b
        if (i - b >= 0)
            combinaciones[i] = mayor(combinaciones[i], combinaciones[i - b]);

        // Comprobar si es posible obtener una pieza de longitud c
        if (i - c >= 0)
            combinaciones[i] = mayor(combinaciones[i], combinaciones[i - c]);

        // Si combinaciones[i] no es -1, significa que se encontró una solución válida,
        // entonces se incrementa en 1 para contar la pieza actual
        if (combinaciones[i] != -1)
            combinaciones[i]++;
    }

    // Devolver la cantidad máxima de piezas de cinta para la longitud original n
    return combinaciones[n];
}

int main() {
    int n, a, b, c;
    printf("Ingrese el largo y los 3 cortes posibles separados por un espacio:");
    scanf("%d %d %d %d", &n, &a, &b, &c);

    int piezas= maxima_cantidad_de_piezas(n, a, b, c);

    printf("La mayor cantidad de cortes es de:%d\n", piezas);

    return 0;
}