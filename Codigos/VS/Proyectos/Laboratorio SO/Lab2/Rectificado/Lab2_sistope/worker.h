#ifndef WORKER_H
#define WORKER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"

// Funciones
void aplicar_filtros_y_guardar(const char* filename, int filters, float saturation, float thresholdbina, const char* csvname);

#endif // WORKER_H