#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "estructuras.h"
#include "funciones.h"

int main(){
    ListaTareas lista;
    lista.num_tareas = 0;
  
    while (true) {
        imprimir_menu();
        int opcion;
        printf("\nIngrese una opción: ");
        scanf("%d", &opcion);
        manejar_opcion(&lista, opcion);
    }


    return 0;
}
/*bool ejecutando = true;
while (ejecutando) {
    imprimir_menu();
    int opcion;
    printf("Ingrese una opción: ");
    scanf("%d", &opcion);
    ejecutando = manejar_opcion(&lista, opcion);
}
*/