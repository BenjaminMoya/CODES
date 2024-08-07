#ifndef BROKER_H
#define BROKER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <bits/getopt_core.h>
#include <string.h>
#include "funciones.h"
// Funciones
void crear_procesos_worker(int workers, char *prefix, int filters, float saturation, float thresholdbina);

#endif // BROKER_H