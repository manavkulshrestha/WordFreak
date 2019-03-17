#include "hashmap.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>  // POSIX NAMES, read, and read

HashMap *hashmap(int size, int collision_handling) {
    HashMap *hash_map = (HashMap *) malloc(sizeof(HashMap));

    *(hash_map->size) = size;

    hash_map->arr = (HashBin **) malloc(size*sizeof(HashBin *));
    for(int i=0; i<size; i++)
        hash_map->arr[i] = NULL;

    *(hash_map->collison_handling) = collison_handling;

    return hash_map;
}

// rudimentory. Feel free to change to make it better @Anthony
int *hash(char *word, int *map_size) {
    int *code = (int *) malloc(sizeof(int));
    *code = 0;

    for(int i=0; i<strlen(word); i++) {
        *code += (int) word[i];
    }

    *code = ((*code)*(*code)) % *map_size;

    return code;
}

void add(HashMap *hash_map, char *word, int frequency) {
    int *index = hash(word, hash_map->size);

    if(hash_map->arr[*index] == NULL) {
        hash_map->arr[*index] = hashbin(word);
    } else {
        if(*collison_handling == COLLISION_CHAINING) {
            // dealing with hash collision using chaining
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
        } else {// *collison_handling == COLLISION_PROBING
            // dealing with hash collision using quadratic probing
            int *initial_index = (int *) malloc(sizeof(int));
            *initial_index = *index;
            
            int *probe = (int *) malloc(sizeof(int)); 
            *probe = 1;

            while(1) {
                if(hash_map->arr[*index] == NULL) {
                    hash_map->arr[*index] = hashbin(word, frequency);
                } else {
                    *index += *probe

                    if(*index == *initial_index) {
                        rehash(hash_map);
                        add(hash_map, word, frequency);
                        break;
                    }
                }

                *probe *= 4;
            }

            free(initial_index);
            initial_index = NULL;

            free(probe);
            probe = NULL;
        }
    }

    free(index);
    index = NULL;
}

void print_sorted(HashMap *hash_map) {
    HashBin **temp_arr = (HashBin **) malloc(*(hash_map->size)*sizeof(HashBin *));
    memcpy(temp_arr, hash_map->arr, *(hash_map->size));

    char *buffer;

    qsort(temp_arr, *(hash_map->size), sizeof(hash_map), compare_bin);

    for(int i=0; i<hash_map->size && temp_arr[i] != NULL; i++) {
        buffer = (char *) malloc(50*sizeof(char));
        sprintf(buffer, "%s:\t\t%i\n", temp_arr[i]->word, *(temp_arr[i]->frequency));

        write(STDOUT_FILENO, buffer, strlen(buffer));

        free(buffer);
        buffer = NULL;
    }
    
    for(int i=0; i<hash_map->size && temp_arr[i] != NULL; i++) {
        free_bin(temp_arr[i]);
        temp_arr[i] = NULL;
    }

    free(temp_arr);
    temp_arr = NULL;
}

void rehash(HashMap *hash_map) {
    HashMap *new_map = hashmap(*(hash_map->size)*2);

    for(int i=0; i<*(hash_map->size); i++)
        if(hash_map->arr[i] != NULL)
            add(new_map, hash_map->word, *(hash_map->frequency));

    free_map(hash_map);
    HashMap *hash_map = hashmap(*(new_map->size));

    memcpy(hash_map->arr, new_map->arr, *(hash_map->size));

    free_map(new_map);
    new_map = NULL;
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

    free(collison_handling);
    collison_handling = NULL;

    free(hash_map);
    hash_map = NULL;
}