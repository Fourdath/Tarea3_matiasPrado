#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "estructuras.h"

//void menu(ListaTareas* lista);
void imprimir_menu();

void manejar_opcion(ListaTareas* lista, int opcion);

void agregar_tarea(ListaTareas* lista, char nombre[MAX_NOMBRE], int prioridad);

bool tarea_visitada(Tarea* tarea, ListaTareas* lista);

void establecer_precedencia(ListaTareas* lista, char nombre_tarea1[MAX_NOMBRE], char nombre_tarea2[MAX_NOMBRE]);

void actualizarPrioridad(ListaTareas* lista);

void mostrar_tareas_por_hacer(ListaTareas* lista);

void marcar_tarea_completada(ListaTareas* lista, const char* nombre);



#endif // FUNCIONES_H
