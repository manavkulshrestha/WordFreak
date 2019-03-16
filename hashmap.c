#include "hashbin.h"
#include "hashmap.h"
#include <string.h>
#include <stdlib.h>

HashMap *hashmap(int size) {
    HashMap *hash_map = (HashMap *) malloc(sizeof(HashMap));

    *(hash_map->size) = size;

    hash_map->arr = (HashBin **) malloc(size*sizeof(HashBin *));
    for(int i=0; i<size; i++)
        hash_map->arr[i] = NULL;

    return hash_map;
}

// rudimentory. Feel free to change to make it better @Anthony
int *hash(char *word, int *map_size) {
    int *code = (int *) malloc(sizeof(int));
    *code = 0;

    for(int i=0; i<strlen(word); i++) {
        *code += (int) word[i];
    }

    *code = (*code * 2) % *map_size;

    return code;
}

void add(HashMap *hash_map, char *word) {
    int *index = hash(word, hash_map->size);

    if(hash_map->arr[*index] == NULL) {
        hash_map->arr[*index] = hashbin(word);
    } else {
        // dealing with hash collision using linked lists
        HashBin *curr = hash_map->arr[*index];
        while(1) {
            if(strcmp(curr->word, word) == 0) {
                (*(curr->frequency))++;
                break;
            } else if(curr->link == NULL) {
                curr->link = hashbin(word);
                break;
            } else {
                curr = curr->link;
            }
        }
    }

    free(index);
    index = NULL;
}

void sort(HashMap *hash_map) {
    qsort(hash_map->arr, *(hash_map->size), sizeof(hash_map), compare_bin);
}

void free_map(HashMap *hash_map) {
    free(hash_map->size);
    hash_map->size = NULL;

    for(int i=0; i<*(hash_map->size); i++) {
        if(hash_map->arr[i] != NULL) {
            free_bin(hash_map->arr[i]);
            hash_map->arr[i] = NULL;
        }
    }
    hash_map = NULL;
}