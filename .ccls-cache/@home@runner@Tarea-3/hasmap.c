#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "define HashMap_h"
#define HashMap_h


typedef struct HashMap HashMap;
int enlarge_called=0;


struct HashMap {
    Pair** buckets;
    long size;
    long capacity; 
    long current; 
};


  
Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    long i = hash(key,map->capacity);

    while(map->buckets[i] != NULL && map->buckets[i]->key != NULL)
    {
        
        if(is_equal(map->buckets[i]->key,key) == 1){
            return;
        } 
        
        i++;
        if (i >= map->capacity) i = 0;
    }

    map->buckets[i] = createPair(key,value);
    map->current = i;
    (map->size)++;

}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)

    if (map->capacity == 0) return;
    
    Pair** aux = map->buckets;
    map->capacity *= 2;
    map->buckets = (Pair **) calloc(map->capacity,sizeof(Pair*));
    map->size = 0;

    for(int i = 0 ; i < map->capacity / 2 ; i++)
        if (aux[i] != NULL && aux[i]->key != NULL)
            insertMap(map,aux[i]->key,aux[i]->value);

    free(aux);
    
}


HashMap * createMap(long capacity) {
    HashMap* newMap = (HashMap *) malloc(sizeof(HashMap));
    newMap->buckets = (Pair **) calloc(capacity,sizeof(Pair *));
    newMap->size = 0;
    newMap->capacity = capacity;
    newMap->current = -1;

    return newMap;
}

void eraseMap(HashMap * map,  char * key) {    
    int i = hash(key,map->capacity);

    while(map->buckets[i] != NULL && is_equal(map->buckets[i]->key,key) != 1)
    {
        i++;
    }

    if (map->buckets[i] == NULL) return;
    map->buckets[i]->key = NULL;
    (map->size)--;


}

Pair * searchMap(HashMap * map,  char * key) {  
    long i = hash(key,map->capacity);
    
    while(map->buckets[i] != NULL && is_equal(map->buckets[i]->key,key) != 1)
    {
        //i = (i + 1) % map->capacity; 
        i++;
    }

    if (map->buckets[i] == NULL) return NULL;
     
    map->current = i;
    return map->buckets[i];
}

Pair * firstMap(HashMap * map) {
    if (map==NULL) return NULL;
    int i = 0;
    while(map->buckets[i] == NULL || map->buckets[i]->key == NULL )
        i++;
    map->current = i;
    return map->buckets[i];
    
}

Pair * nextMap(HashMap * map) {
    if (map->current > map->capacity) return NULL;
    int i = (map->current) + 1;
    while(map->buckets[i] == NULL || map->buckets[i]->key == NULL ){
        i++;
        if (i >= map->capacity) return NULL;
    }
    map->current = i;
    return map->buckets[i];

}

bool existenJugadores(HashMap * map)
{
    if(map->size==0)return false;
    return true;
}