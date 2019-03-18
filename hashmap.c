#include "hashmap.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>  // POSIX NAMES, read, and read
#include <stdio.h> // sprintf

/* CONSTRUCTOR */
HashMap *hashmap(int size) {
    HashMap *hash_map = (HashMap *) malloc(sizeof(HashMap));

    hash_map->size = (int *) malloc(sizeof(int));
    *(hash_map->size) = size;

    hash_map->arr = (HashBin **) malloc(size*sizeof(HashBin *));
    for(int i=0; i<size; i++)
        hash_map->arr[i] = NULL;

    return hash_map;
}

// rudimentory. Feel free to change to make it better @Anthony
/*
    Arguments:
        char *word - Word to get hash for.
        int *map_size - size of the hashmap.

    Description:
        Produces a hash for the provided word using the map_size.

    Returns:
        int *code - hash produced.
*/
int *hash(char *word, int *map_size) {
    int *code = (int *) malloc(sizeof(int));
    *code = 0;

    for(int i=0; i<strlen(word); i++) {
        *code += (int) word[i];
    }

    *code = ((*code)*(*code)) % *map_size;

    return code;
}

/* 
    Arguments:
        HashMap *hash_map - HashMap to add the word in.
        char *word - The word to add.

    Description:
        Adds the word into the hash_map provided. If the word already exists in the hash_map, its
        frequency is incremented by 1 else it is initialized as 1. It is capable of handling collisions by either chaining or
        quadratic probing, depending how how the hash_map was initialized. Note that it automatically
        calls rehash() in the even that hash_map is full quandratic probing is being used.

    Returns:
        int ret - index of where the word is positioned in the hash_map's array.
*/
int add(HashMap *hash_map, char *word) {
    int *index = hash(word, hash_map->size);

    if(hash_map->arr[*index] == NULL) {
        hash_map->arr[*index] = hashbin(word, 1);
    } else {
        // dealing with hash collision using quadratic probing
        int *initial_index = (int *) malloc(sizeof(int));
        *initial_index = *index;
        
        int *probe = (int *) malloc(sizeof(int));
        *probe = 1;

        while(1) {
            if(hash_map->arr[*index] == NULL) {
                hash_map->arr[*index] = hashbin(word, 1);
                break;
            } else if(strcmp(hash_map->arr[*index]->word, word) == 0) {
                (*(hash_map->arr[*index]->frequency))++;
                break;
            } else {
                *index += *probe;

                if(*index == *initial_index) {
                    rehash(hash_map);
                    add(hash_map, word);
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

    int ret = *index;
    free(index);
    index = NULL;

    return ret;
}


/* 
    Arguments:
        HashMap *hash_map - the HashMap to print.

    Description:
        Prints the hash_map provided, sorted by frequency using the compare_bin() funcion.
        Makes a copy of the underlying array and sorts he copy so the positions of the
        elements is not disturbed in the old array.
*/
void print_sorted(HashMap *hash_map) {
    HashBin **temp_arr = (HashBin **) malloc(*(hash_map->size)*sizeof(HashBin *));
    memcpy(temp_arr, hash_map->arr, *(hash_map->size));

    char *buffer;

    qsort(temp_arr, *(hash_map->size), sizeof(hash_map), reverse_compare_bin);

    for(int i=0; i<*(hash_map->size) && temp_arr[i] != NULL; i++) {
        buffer = (char *) malloc(50*sizeof(char));
        sprintf(buffer, "%s:\t\t%i\n", temp_arr[i]->word, *(temp_arr[i]->frequency));

        write(STDOUT_FILENO, buffer, strlen(buffer));

        free(buffer);
        buffer = NULL;
    }
    
    for(int i=0; i<*(hash_map->size) && temp_arr[i] != NULL; i++) {
        free_bin(temp_arr[i]);
        temp_arr[i] = NULL;
    }

    free(temp_arr);
    temp_arr = NULL;
}

/*
    Arguments:
        char *format - Format string for how to print HashBin. Must contain %s and %i in that order.
        HashMap *hash_map - the HashMap to print.

    Description:
        Prints the hash_map provided, formatted in the way outlined by format
*/
void print_map(char *format, HashMap *hash_map) {
    char *buffer = (char *) malloc(50*sizeof(char));

    for(int i=0; i<*(hash_map->size); i++) {
        if(hash_map->arr[i] != NULL) {
            sprintf(buffer, format, hash_map->arr[i]->word, *(hash_map->arr[i]->frequency));
            write(STDOUT_FILENO, buffer, strlen(buffer));
        }
    }
            
    free(buffer);
    buffer = NULL;
}

/*
    Arguments:
        HashMap *hash_map - hash_map to rehash

    Description:
        Doubles the size of the underlying array and re-adds the existing elements.

*/
void rehash(HashMap *hash_map) {
    write(STDOUT_FILENO, "REHASH TRIGGERED\n", strlen("REHASH TRIGGERED\n"));
    HashMap *new_map = hashmap(*(hash_map->size)*2);

    for(int i=0; i<*(hash_map->size); i++) {
        if(hash_map->arr[i] != NULL) {
            new_map->arr[add(new_map, hash_map->arr[i]->word)]->frequency = hash_map->arr[i]->frequency;
        }
    }

    free_map(hash_map);
    hash_map = hashmap(*(new_map->size));

    memcpy(hash_map->arr, new_map->arr, *(hash_map->size));

    free_map(new_map);
    new_map = NULL;
}
/*
    Arguments:
        HashMap *hash_map - HashMap to free

    Description:
        Frees the provided hash_map.
*/
void free_map(HashMap *hash_map) {
    free(hash_map->size);
    hash_map->size = NULL;

    for(int i=0; i<*(hash_map->size); i++) {
        if(hash_map->arr[i] != NULL) {
            free_bin(hash_map->arr[i]);
            hash_map->arr[i] = NULL;
        }
    }

    free(hash_map);
    hash_map = NULL;
}