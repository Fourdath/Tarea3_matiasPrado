#include <stdlib.h>
#include "estructuras.h"

typedef struct Heap {
    Tarea* elementos[MAX_TAREAS];
    int num_elementos;
} Heap;

Heap* crear_monticulo() {
    Heap* monticulo = malloc(sizeof(Heap));
    monticulo->num_elementos = 0;
    return monticulo;
}

void insertar_en_monticulo(Heap* monticulo, Tarea* tarea, int prioridad) {
    if (monticulo->num_elementos == MAX_TAREAS) {
        return;  // El montículo está lleno, no se puede insertar más elementos
    }
    
    int i = monticulo->num_elementos;
    while (i > 0 && monticulo->elementos[(i - 1) / 2]->prioridad > prioridad) {
        monticulo->elementos[i] = monticulo->elementos[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    
    monticulo->elementos[i] = tarea;
    monticulo->num_elementos++;
}

Tarea* eliminar_minimo(Heap* monticulo) {
    if (monticulo->num_elementos == 0) {
        return NULL;  // El montículo está vacío, no se puede eliminar ningún elemento
    }
    
    Tarea* minimo = monticulo->elementos[0];
    monticulo->num_elementos--;
    
    Tarea* ultimo = monticulo->elementos[monticulo->num_elementos];
    int i = 0;
    while (2 * i + 1 < monticulo->num_elementos) {
        int hijo_izquierdo = 2 * i + 1;
        int hijo_derecho = 2 * i + 2;
        int hijo_menor = hijo_izquierdo;
        
        if (hijo_derecho < monticulo->num_elementos && monticulo->elementos[hijo_derecho]->prioridad < monticulo->elementos[hijo_izquierdo]->prioridad) {
            hijo_menor = hijo_derecho;
        }
        
        if (ultimo->prioridad <= monticulo->elementos[hijo_menor]->prioridad) {
            break;
        }
        
        monticulo->elementos[i] = monticulo->elementos[hijo_menor];
        i = hijo_menor;
    }
    
    monticulo->elementos[i] = ultimo;
    
    return minimo;
}

int esta_vacio_monticulo(Heap* monticulo) {
    return monticulo->num_elementos == 0;
}

void liberar_monticulo(Heap* monticulo) {
    free(monticulo);
}
