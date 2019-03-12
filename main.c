#include <stdio.h> // printf
#include <sys/stat.h> // open
#include <unistd.h>  // POSIX NAMES and read
#include <fcntl.h> // open flags
#include <stdlib.h> // for malloc
#include <errno.h>
#include "hashmap.h"

#define BUFFER_LEN 100
// #define MAP_LEN 131 // Arbitrary prime number, will be changed later if more capacity is needed
#define MAP_LEN 5000

/*
MAIN FUNCTION REVAMP (remove io functions etc)
JUMP EFFIENCIENY
REHASH FUNCTION (increase size)
HASH FUNCTION
*/

int main(int argc, char *argv[], char *envp[]) {
    HashEntry *hash_map[MAP_LEN];

    if(argc < 2) {
        printf("Not enough arguments. argc = %i", argc);
        return argc;
    }

    for(int i = 1; i < argc; i++) {
        int *text = (int *) malloc(sizeof(int));
        *text = open(argv[i], O_RDONLY); // reading only

        if(*text == -1) {
            printf("Error opening file %i: errno = %i\n", i, errno);
            return errno;
        }

        char *buffer = (char *) malloc(BUFFER_LEN*sizeof(char *)); // allocating buffer
        int *bytes_read = (int *) malloc(sizeof(int));

        do {
            *bytes_read = read(*text, buffer, BUFFER_LEN-1);
            buffer[*bytes_read] = '\0'; // adding null terminating character at the end of bytes read
            printf("%s", buffer);
        } while(*bytes_read != 0);


        if(close(*text) == -1) {  // closing file
            printf("Error closing file %i: errno = %i\n", i, errno);
            return errno;
        }

        free(text);
        text = NULL;

        free(buffer);
        buffer = NULL;

        free(bytes_read);
        bytes_read = NULL;
    }
    return 0;
}