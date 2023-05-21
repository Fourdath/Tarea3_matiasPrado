#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "estructuras.h"
#include "funciones.h"
#include "heap.h"
#include "hashmap.h"
#include "listas.h"




void imprimir_menu() {
    printf("\n===== Menú de opciones =====\n");
    printf("1. Agregar tarea\n");
    printf("2. Establecer relación de precedencia\n");
    printf("3. Mostrar lista de tareas\n");
    printf("4. Marcar como completada\n");
    printf("5. Leer archivo csv\n");
    printf("6. Salir\n");
}
void manejar_opcion(ListaTareas* lista, int opcion) {
    char nombre[MAX_NOMBRE]; // mueve esta línea al inicio de la función
    int prioridad;
    char nombre_tarea1[MAX_NOMBRE];
    char nombre_tarea2[MAX_NOMBRE];
    char nombre_archivo[MAX_NOMBRE];
    switch (opcion) {
        case 1:
            // agregar tarea
            printf("Ingrese el nombre de la tarea: ");
            scanf("%s", nombre);
            printf("Ingrese la prioridad de la tarea: ");
            scanf("%d", &prioridad);
            agregar_tarea(lista, nombre, prioridad);
            break;
        case 2:
            // establecer relación de precedencia
            
            printf("Ingrese el nombre de la tarea1: ");
            scanf("%s", nombre_tarea1);
            printf("Ingrese el nombre de la tarea2: ");
            scanf("%s", nombre_tarea2);
            establecer_precedencia(lista, nombre_tarea1, nombre_tarea2);
            

            break;
        case 3:
            // mostrar tareas por hacer
            mostrar_tareas_por_hacer(lista);
            break;
        case 4:
            printf("Ingrese el nombre de la tarea a marcar como completada: ");
            scanf("%s", nombre);
            marcar_tarea_completada(lista, nombre);
            break;
        case 5:
            // guardar lista de tareas en archivo
            printf("Ingrese el nombre del archivo: ");
            scanf("%s", nombre_archivo);
            
            break;
        case 6:
            // salir
            exit(0);
            break;
        default:
            printf("Opción inválida. Por favor ingrese un número del 1 al 6.\n");
            break;
    }
}

/////////////////////////////////////////

void agregar_tarea(ListaTareas* lista, char nombre[MAX_NOMBRE], int prioridad) {
    // verificar si hay espacio en la lista
    if (lista->num_tareas >= MAX_TAREAS) {
        printf("Error: no hay espacio para agregar más tareas.\n");
        return;
    }

    // crear la tarea y agregarla a la lista
    Tarea* tarea_nueva = malloc(sizeof(Tarea));
    strcpy(tarea_nueva->nombre, nombre);
    tarea_nueva->prioridad = prioridad;
    tarea_nueva->num_tareas_precedentes = 0;

    // pedir las tareas precedentes
    int num_precedentes;
    printf("Ingrese el número de tareas precedentes: ");
    scanf("%d", &num_precedentes);

    for (int i = 0; i < num_precedentes; i++) {
        char nombre_precedente[MAX_NOMBRE];
        printf("Ingrese el nombre de la tarea precedente #%d: ", i+1);
        scanf("%s", nombre_precedente);

        // buscar la tarea precedente en la lista
        int j;
        for (j = 0; j < lista->num_tareas; j++) {
            if (strcmp(lista->tareas[j]->nombre, nombre_precedente) == 0) {
                // tarea precedente encontrada, agregarla a la nueva tarea
                tarea_nueva->tareas_precedentes[tarea_nueva->num_tareas_precedentes] = lista->tareas[j];
                tarea_nueva->num_tareas_precedentes++;

                // aumentar el número de tareas dependientes en la tarea precedente
                lista->tareas[j]->num_tareas_precedentes++;
                break;
            }
        }

        if (j == lista->num_tareas) {
            // tarea precedente no encontrada en la lista
            printf("Error: la tarea precedente #%d (%s) no existe en la lista.\n", i+1, nombre_precedente);
            free(tarea_nueva);
            return;
        }
    }

    lista->tareas[lista->num_tareas] = tarea_nueva;
    lista->num_tareas++;
    printf("Tarea %s agregada con éxito.\n", nombre);
}


//////////////////////////////////////

bool tarea_visitada(Tarea* tarea, ListaTareas* lista) {
    for (int i = 0; i < lista->num_tareas; i++) {
        if (lista->tareas[i] == tarea) {
            return true;
        }
    }
    return false;
}

/////////////////////////////////////////////////////////////////////

void establecer_precedencia(ListaTareas* lista, char nombre_tarea1[MAX_NOMBRE], char nombre_tarea2[MAX_NOMBRE]) {
    Tarea* tarea1 = NULL;
    Tarea* tarea2 = NULL;

    // Buscar las tareas en la lista
    for (int i = 0; i < lista->num_tareas; i++) {
        if (strcmp(lista->tareas[i]->nombre, nombre_tarea1) == 0) {
            tarea1 = lista->tareas[i];
        }
        if (strcmp(lista->tareas[i]->nombre, nombre_tarea2) == 0) {
            tarea2 = lista->tareas[i];
        }
    }

    // Verificar si se encontraron las tareas
    if (tarea1 == NULL || tarea2 == NULL) {
        printf("Error: una o ambas tareas no existen en la lista.\n");
        return;
    }

    // Verificar si la tarea2 ya es precedente de la tarea1
    for (int i = 0; i < tarea1->num_tareas_precedentes; i++) {
        if (tarea1->tareas_precedentes[i] == tarea2) {
            printf("Error: la tarea %s ya es precedente de la tarea %s.\n", nombre_tarea2, nombre_tarea1);
            return;
        }
    }

    // Establecer la precedencia entre las tareas
    tarea1->tareas_precedentes[tarea1->num_tareas_precedentes] = tarea2;
    tarea1->num_tareas_precedentes++;

    printf("Se estableció la precedencia entre la tarea %s y la tarea %s.\n", nombre_tarea1, nombre_tarea2);
}



//////////////////////////////////////////////////////////////////////////////

void mostrar_tareas_por_hacer(ListaTareas* lista) {
    // Crear un montículo de mínimos
    Heap* monticulo = crear_monticulo();
    int tamano_monticulo = 0;

    // Crear un hashmap para buscar tareas por nombre
    HashMap* hashmap = crear_hashmap();
    int tamano_hashmap = 0;

    // Crear una lista de tareas realizadas
    TareasList* lista_realizadas = crear_lista_tareas();
    
    while (lista->num_tareas > 0 || tamano_monticulo > 0) {
        // Recorrer la lista
        for (int i = 0; i < lista->num_tareas; i++) {
            Tarea* tarea = lista->tareas[i];

            // Caso 1: Agregar tareas sin tareas precedentes al montículo
            if (tarea->num_tareas_precedentes == 0) {
                insertar_en_monticulo(monticulo, tarea, tarea->prioridad);
                agregar_tarea_lista(lista_realizadas, tarea);
                agregar_tarea_hashmap(hashmap, tarea);
                eliminar_tarea_lista(lista, tarea);
                tamano_monticulo++;
            }
            // Caso 2: La tarea tiene tareas precedentes
            else {
                int num_precedentes_en_hashmap = 0;
                for (int j = 0; j < tarea->num_tareas_precedentes; j++) {
                    Tarea* precedente = tarea->tareas_precedentes[j];
                    if (buscar_tarea_hashmap(hashmap, precedente->nombre) != NULL) {
                        num_precedentes_en_hashmap++;
                    }
                }
                // Si todas las tareas precedentes están en el hashmap, se elimina la tarea precedente de la lista
                if (num_precedentes_en_hashmap == tarea->num_tareas_precedentes) {
                    eliminar_tarea_lista(lista, tarea);
                }
            }
        }

        // Ordenar el montículo por prioridad
        for (int i = 0; i < tamano_monticulo - 1; i++) {
            for (int j = i + 1; j < tamano_monticulo; j++) {
                if (monticulo->elementos[j]->prioridad < monticulo->elementos[i]->prioridad) {
                    Tarea* temp = monticulo->elementos[i];
                    monticulo->elementos[i] = monticulo->elementos[j];
                    monticulo->elementos[j] = temp;
                }
            }
        }

        // Extraer la tarea de menor prioridad del montículo
        Tarea* tarea_extraida = eliminar_minimo(monticulo);
        tamano_monticulo--;

        // Agregar la tarea a la lista de tareas realizadas y al hashmap
        agregar_tarea_lista(lista_realizadas, tarea_extraida);
        agregar_tarea_hashmap(hashmap, tarea_extraida);
    }

    // Mostrar la lista de tareas realizadas
    printf("Tareas por hacer, ordenadas por prioridad y precedencia:\n");
    for (int i = 0; i < lista_realizadas->num_tareas; i++) {
        Tarea* tarea = lista_realizadas->cabeza->tarea;
        printf("%d. %s (Prioridad: %d)", i + 1, tarea->nombre, tarea->prioridad);

        // Mostrar las tareas precedentes, si las hay
        if (tarea->num_tareas_precedentes > 0) {
            printf(" - Precedente: ");
            for (int j = 0; j < tarea->num_tareas_precedentes; j++) {
                printf("%s", tarea->tareas_precedentes[j]->nombre);
                if (j < tarea->num_tareas_precedentes - 1) {
                    printf(", ");
                }
            }
        }

        printf("\n");
    }

    // Liberar la memoria utilizada por las estructuras de datos auxiliares
    liberar_monticulo(monticulo);
    liberar_hashmap(hashmap);
    liberar_lista_tareas(lista_realizadas);
}

/////////////////////////////////////////////////////////////////////////////

void marcar_tarea_completada(ListaTareas* lista, const char* nombre) {
    // Buscar la tarea por nombre en la lista de tareas por hacer
    int indice = -1;
    for (int i = 0; i < lista->num_tareas; i++) {
        if (strcmp(lista->tareas[i]->nombre, nombre) == 0) {
            indice = i;
            break;
        }
    }

    // Verificar si se encontró la tarea
    if (indice != -1) {
        Tarea* tarea = lista->tareas[indice];
        // Verificar si la tarea tiene tareas precedentes
        if (tarea->num_tareas_precedentes > 0) {
            printf("¿Estás seguro que deseas eliminar la tarea \"%s\"? (S/N): ", tarea->nombre);
            char respuesta;
            scanf(" %c", &respuesta);
            if (respuesta == 'N' || respuesta == 'n') {
                printf("La tarea no ha sido eliminada.\n");
                return;
            }
        }

        // Eliminar la tarea de las tareas precedentes de otras tareas
        for (int i = 0; i < lista->num_tareas; i++) {
            Tarea* tarea_actual = lista->tareas[i];
            for (int j = 0; j < tarea_actual->num_tareas_precedentes; j++) {
                if (tarea_actual->tareas_precedentes[j] == tarea) {
                    // Eliminar la tarea de las tareas precedentes
                    for (int k = j; k < tarea_actual->num_tareas_precedentes - 1; k++) {
                        tarea_actual->tareas_precedentes[k] = tarea_actual->tareas_precedentes[k + 1];
                    }
                    tarea_actual->num_tareas_precedentes--;
                    break;
                }
            }
        }

        // Eliminar la tarea de la lista de tareas por hacer
        eliminar_tarea_lista(lista, tarea);
        printf("La tarea \"%s\" ha sido marcada como completada y eliminada de la lista de tareas por hacer.\n", nombre);
    } else {
        printf("No se encontró la tarea \"%s\" en la lista de tareas por hacer.\n", nombre);
    }
}