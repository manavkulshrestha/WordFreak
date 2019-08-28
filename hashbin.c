#include "hashbin.h"
#include <stdio.h> // printf
#include <sys/stat.h> // open
#include <unistd.h>  // POSIX NAMES and read
#include <fcntl.h> // open flags
#include <stdlib.h> // for malloc
#include <errno.h>
#include <string.h>

/*
    Arguments:
        char *buffer - String to write to STDOUT

    Description:
        Writes to standard out with write(), and performs an error check on the call
*/
void write_with_error_check(char *buffer) {
    if(write(STDOUT_FILENO, buffer, strlen(buffer)) == -1) {
        sprintf(buffer, "Error in writing to STDOUT_FILENO. errno = %i", errno);
        write(STDOUT_FILENO, buffer, strlen(buffer));
        exit(errno);
    }
}

/* CONSTRUCTOR */
HashBin *hashbin(char *word, int frequency) { 
    HashBin *new_bin = (HashBin *) malloc(sizeof(HashBin));
    if(new_bin == NULL) {
        exit(-1);
    }

    int *len = (int *) malloc(sizeof(int));
    if(len == NULL) {
        exit(-1);
    }
    *len = strlen(word);
    new_bin->word = (char *) malloc((++(*len))*sizeof(char));
    if(new_bin->word == NULL) {
        exit(-1);
    }
    strncpy(new_bin->word, word, *len);

    new_bin->frequency = (int *) malloc(sizeof(int));
    if(new_bin->frequency == NULL) {
        exit(-1);
    }
    *(new_bin->frequency) = frequency;

    new_bin->link = NULL;

    free(len);
    len = NULL;

    return new_bin;
}

/*
    Arguments:
        HashBin *hash_map - HashBin to free

    Description:
        Frees the provided hash_bin.
*/
void free_bin(HashBin *hash_bin) {
    if(hash_bin == NULL)
        return;

    free(hash_bin->word);
    hash_bin->word = NULL;

    free(hash_bin->frequency);
    hash_bin->frequency = NULL;

    free_bin(hash_bin->link);
    hash_bin->link = NULL;

    free(hash_bin);
}