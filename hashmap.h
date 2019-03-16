#ifndef HASHMAP_H_
#define HASHMAP_H_

typedef struct HashMap {
    int *size;
    HashBin **arr;
} HashMap;

HashMap *hashmap(int size); 
int *hash(char *word, int *map_size);
void add(HashMap *hash_map, char *word);
void sort(HashMap *map);
void free_map(HashMap *map);

#endif