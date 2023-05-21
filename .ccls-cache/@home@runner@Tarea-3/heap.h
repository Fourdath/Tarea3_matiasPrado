#ifndef HEAP_H
#define HEAP_H

typedef struct HeapStruct {
    Tarea** elementos;  // Array de punteros a tareas
    int capacidad;      // Capacidad máxima del montículo
    int tamano;         // Número actual de elementos en montículo
} Heap;

// Declaraciones de funciones del montículo (heap)
Heap* crear_monticulo();
void insertar_en_monticulo(Heap* monticulo, Tarea* tarea, int prioridad);
void* eliminar_minimo(Heap* monticulo);
int esta_vacio_monticulo(Heap* monticulo);
void liberar_monticulo(Heap* monticulo);

#endif // HEAP_H