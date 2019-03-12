#ifndef HASHMAP_H_
#define HASHMAP_H_

typedef struct hashentry {
    char *word;
    int *frequency;
    HashEntry *link;
} HashEntry;

HashEntry *hashentry(char *word);
int *hash(char *word);
void add(int map_len, HashEntry *hash_map[map_len], char *word);

#endif