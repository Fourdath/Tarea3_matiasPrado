#ifndef HASHSET_H
#define HASHSET_H

#include <stddef.h>

typedef struct HashSet {
    char** elementos;
    int capacidad;
    int tamaño;
} HashSet;

HashSet* crearHashSet();
void destruirHashSet(HashSet* set);
int agregarElemento(HashSet* set, const char* elemento);
int contieneElemento(HashSet* set, const char* elemento);

#endif /* HASHSET_H */

