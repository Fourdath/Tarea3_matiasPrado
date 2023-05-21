#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define MAX_TAREAS 100
#define MAX_NOMBRE 50
#define MAX_TAREAS_PRECEDENTES 10

typedef struct Tarea {
    char nombre[MAX_NOMBRE + 1];
    int prioridad;
    int num_tareas_precedentes;
    struct Tarea* tareas_precedentes[MAX_TAREAS_PRECEDENTES];
    struct Tarea* siguiente; 
} Tarea;

typedef struct ListaTareas {
    int num_tareas;
    Tarea** cabeza;
    Tarea* tareas[MAX_TAREAS];
} ListaTareas;





#endif // ESTRUCTURAS_H
