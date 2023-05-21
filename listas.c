#include <stdlib.h>
#include <string.h>
#include "estructuras.h"

ListaTareas* crear_lista_tareas() {
    ListaTareas* lista = malloc(sizeof(ListaTareas));
    lista->num_tareas = 0;
    lista->cabeza = NULL;
    return lista;
}

void agregar_tarea_lista(ListaTareas* lista, Tarea* tarea) {
    if (lista->cabeza == NULL) {
        lista->cabeza = malloc(sizeof(Tarea*));
        *(lista->cabeza) = tarea;
    } else {
        Tarea** nodo_actual = &(lista->cabeza);
        while (*nodo_actual != NULL) {
            nodo_actual = &((*nodo_actual)->siguiente);
        }
        *nodo_actual = malloc(sizeof(Tarea));
        **nodo_actual = *tarea;
    }
    lista->num_tareas++;
}


void eliminar_tarea_lista(ListaTareas* lista, const char* nombre){
    Tarea** nodo_actual = lista->cabeza;
    Tarea** nodo_anterior = NULL;

    while (*nodo_actual != NULL) {
        if (strcmp((*nodo_actual)->nombre, nombre) == 0) {
            if (nodo_anterior == NULL) {
                lista->cabeza = &((*nodo_actual)->siguiente);
            } else {
                (*nodo_anterior)->siguiente = (*nodo_actual)->siguiente;
            }
            free(*nodo_actual);
            lista->num_tareas--;
            return;
        }

        nodo_anterior = nodo_actual;
        nodo_actual = &((*nodo_actual)->siguiente);
    }
}

void liberar_lista_tareas(ListaTareas* lista) {
    Tarea** nodo_actual = lista->cabeza;
    while (*nodo_actual != NULL) {
        Tarea** nodo_siguiente = &((*nodo_actual)->siguiente);
        free(*nodo_actual);
        nodo_actual = nodo_siguiente;
    }
    free(lista);
}

