#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "hashbin.h"

#define COLLISION_CHAINING 1
#define COLLISION_PROBING 2

typedef struct HashMap {
    int *size;
    HashBin **arr;
    int *collison_handling;
} HashMap;

HashMap *hashmap(int size); 
int *hash(char *word, int *map_size);
void add(HashMap *hash_map, char *word);
void print_sorted(HashMap *map);
void rehash(HashMap *hash_map);
void free_map(HashMap *map);

#endif