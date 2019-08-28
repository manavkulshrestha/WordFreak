#include "hashmap.h"
#include <string.h> //strlen, strcmp
#include <stdlib.h> // malloc, free
#include <unistd.h>  // POSIX NAMES, read, and read
#include <stdio.h> // sprintf
#include <errno.h> // errno

/* CONSTRUCTOR */
HashMap *hashmap(int size) {
    HashMap *hash_map = (HashMap *) malloc(sizeof(HashMap));
    if(hash_map == NULL) {
        exit(-1);
    }

    hash_map->size = (int *) malloc(sizeof(int));
    if(hash_map->size == NULL) {
        exit(-1);
    }
    *(hash_map->size) = size;

    hash_map->arr = (HashBin **) malloc(size*sizeof(HashBin *));
    if(hash_map->arr == NULL) {
        exit(-1);
    }
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

int *hash (char *word, int *size) {
    int *length = (int *) malloc(sizeof(int));
    if(length == NULL) {
        exit(-1);
    }
    *length = strlen(word) / 4;

    long *sum = (long *) malloc(sizeof(long));
    if(sum == NULL) {
        exit(-1);
    }
    *sum = 0;

    char *c = (char *) malloc(strlen(word) * sizeof(char));
    if(c == NULL) {
        exit(-1);
    }

    int *i = (int *) malloc(sizeof(int));
    if(i == NULL) {
        exit(-1);
    }

    long *mult = (long *) malloc(sizeof(long));
    if(mult == NULL) {
        exit(-1);
    }

    for (int j = 0; j < *length; j++) {
        for(*i = j*4; *i < (j*4)+4; (*i)++)
            c[*i-j*4] = word[*i];
        c[*i] = '\0';
        
        *mult = 1;
        for (int k = 0; k < strlen(c); k++) {
	        *sum += c[k] * (*mult);
	        *mult *= 256;
        }
    }

    for(*i = *length*4; *i < strlen(word); (*i)++)
        c[*i - (*length*4)] = word[*i];
    *mult = 1;
    for (int k = 0; k < strlen(c); k++) {
        *sum += c[k] * (*mult);
        *mult *= 256;
    }

    free(length);
    length = NULL;

    free(c);
    c = NULL;

    free(i);
    i = NULL;

    free(mult);
    mult = NULL;

    int *result = (int *) malloc(sizeof(int));
    if(result == NULL) {
        exit(-1);
    }
    *result = (((*sum >= 0) ? *sum : -*sum) % *size);
    return result;
}

/* 
    Arguments:
        HashMap *hash_map - HashMap to add the word in.
        char *word - The word to add.

    Description:
        Adds the word into the hash_map provided. If the word already exists in the hash_map, its
        frequency is incremented by 1 else it is initialized as 1. It is capable of handling collisions
        by chaining.
*/
void add(HashMap *hash_map, char *word) {
    int *index = hash(word, hash_map->size);

    if(hash_map->arr[*index] == NULL) {
        hash_map->arr[*index] = hashbin(word, 1);
    } else {
        HashBin *curr = hash_map->arr[*index];

        while(1) {
            if(strcmp(curr->word, word) == 0) {
                (*(curr->frequency))++;
                break;
            } else if(curr->link == NULL) {
                curr->link = hashbin(word, 1);
                break;
            } else {
                curr = curr->link;
            }
        }
    }
}

/*
    Arguments:
        char *format - Format string for how to print HashBin. Must contain %s and %i in that order.
        HashMap *hash_map - the HashMap to print.

    Description:
        Prints the hash_map provided, formatted in the way outlined by format.
*/
void print_map(char *format, HashMap *hash_map) {
    char *buffer = (char *) malloc(100*sizeof(char));
    if(buffer == NULL) {
        exit(-1);
    }

    for(int i=0; i<*(hash_map->size); i++) {
        if(hash_map->arr[i] != NULL) { // print all bins
            HashBin *curr = hash_map->arr[i];

            while(curr != NULL) { // print chain
                sprintf(buffer, format, curr->word, *(curr->frequency));
                
                if(write(STDOUT_FILENO, buffer, strlen(buffer)) == -1) {// checking for write failure
                    sprintf(buffer, "Error in writing to STDOUT_FILENO. errno = %i", errno);
                    write(STDOUT_FILENO, buffer, strlen(buffer));
                    exit(errno);
                }

                curr = curr->link;
            }
        }
    }
            
    free(buffer);
    buffer = NULL;
}

/*
    Arguments:
        HashMap *hash_map - HashMap to free

    Description:
        Frees the provided hash_map.
*/
void free_map(HashMap *hash_map) {
    for(int i=0; i<*(hash_map->size); i++) {// free's arr
        if(hash_map->arr[i] != NULL) {
            free_bin(hash_map->arr[i]);
            hash_map->arr[i] = NULL;
        }
    }

    free(hash_map->size);
    hash_map->size = NULL;

    free(hash_map);
}