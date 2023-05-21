#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdlib.h>
#include <string.h>
#include "estructuras.h"

typedef struct HashMap {
    Tarea* elementos[MAX_TAREAS][2];  // Matriz de punteros a tareas (nombre y tarea)
    int num_elementos;
} HashMap;

HashMap* crear_hashmap();
void agregar_tarea_hashmap(HashMap* hashmap, Tarea* tarea);
Tarea* buscar_tarea_hashmap(HashMap* hashmap, const char* nombre);
void liberar_hashmap(HashMap* hashmap);

#endif  // HASHMAP_H
