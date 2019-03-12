#ifndef HASHMAP_H_
#define HASHMAP_H_

typedef struct hashentry {
    char *word;
    int *frequency;
} HashEntry;

HashEntry *hashentry(char *word);
int *hash(char *word);
int add(HashEntry *hash_map, char *word);

#endif