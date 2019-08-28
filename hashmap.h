#ifndef HASHMAP_H_
#define HASHMAP_H_

#include "hashbin.h"

typedef struct HashMap {
    int *size;
    HashBin **arr;
} HashMap;

HashMap *hashmap(int size);
int *hash(char *word, int *size);
void add(HashMap *hash_map, char *word);
void print_map(char *format, HashMap *hash_map);
void free_map(HashMap *map);

#endif