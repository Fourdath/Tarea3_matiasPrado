#include <stdlib.h>
#include <string.h>
#include "estructuras.h"

typedef struct HashMap {
    int num_elementos;
    Tarea* elementos[MAX_TAREAS];
} HashMap;

HashMap* crear_hashmap() {
    HashMap* hashmap = malloc(sizeof(HashMap));
    hashmap->num_elementos = 0;
    memset(hashmap->elementos, 0, sizeof(hashmap->elementos));  // Inicializar todos los punteros a NULL
    return hashmap;
}

void agregar_tarea_hashmap(HashMap* hashmap, Tarea* tarea) {
    if (hashmap->num_elementos == MAX_TAREAS) {
        return;  // El hashmap está lleno, no se puede agregar más elementos
    }

    // Buscar una posición libre en el hashmap
    int i = 0;
    while (hashmap->elementos[i] != NULL) {
        i++;
    }

    // Agregar la tarea al hashmap
    hashmap->elementos[i] = tarea;
    hashmap->num_elementos++;
}

Tarea* buscar_tarea_hashmap(HashMap* hashmap, const char* nombre) {
    for (int i = 0; i < hashmap->num_elementos; i++) {
        if (strcmp(hashmap->elementos[i]->nombre, nombre) == 0) {
            return hashmap->elementos[i];
        }
    }
    return NULL;  // No se encontró la tarea en el hashmap
}

void liberar_hashmap(HashMap* hashmap) {
    free(hashmap);
}

