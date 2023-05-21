#ifndef LISTAS_H
#define LISTAS_H

#include "estructuras.h"

typedef struct Nodo {
    Tarea* tarea;
    struct Nodo* siguiente;
} Nodo;

typedef struct TareasList {
    Nodo* cabeza;
    int num_tareas;
} TareasList;

TareasList* crear_lista_tareas();
void agregar_tarea_lista(TareasList* lista, Tarea* tarea);
void eliminar_tarea_lista(TareasList* lista, Tarea* tarea);
void liberar_lista_tareas(TareasList* lista);

#endif /* LISTAS_H */
