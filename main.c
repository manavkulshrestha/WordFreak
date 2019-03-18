#include <stdio.h> // printf
#include <sys/stat.h> // open
#include <unistd.h>  // POSIX NAMES and read
#include <fcntl.h> // open flags
#include <stdlib.h> // for malloc
#include <errno.h>
#include <string.h>
#include "hashbin.h"
#include "hashmap.h"

// #define IS_WHITESPACE(c) c == ' ' || c == '\n'
#define IS_ALPHANUMERIC(c) ('A' <= (c) && (c) <= 'Z') || ('a' <= (c) && (c) <= 'z') || ('0' <= (c) && (c) <= '9')

#define MAX_WORD_LEN 30
#define MAP_SIZE 5000

int open_file(char *file_name, int flags) {
    int *text = (int *) malloc(sizeof(int)); // File descriptor
    *text = open(file_name, flags); // reading only
    char *print_buffer = (char *) malloc(50*sizeof(char));    

    if(*text == -1) {
        sprintf(print_buffer, "Error reading file: errno = %i", errno);
        write(STDOUT_FILENO, print_buffer, strlen(print_buffer));
        exit(errno);
    }

    free(print_buffer);
    print_buffer = NULL;

    return *text;
}

void close_file(int *file_descriptor) {
    char *print_buffer = (char *) malloc(50*sizeof(char));

    if(close(*file_descriptor) == -1) {  // closing file
        sprintf(print_buffer, "Error closing file: errno = %i", errno);
        write(STDOUT_FILENO, print_buffer, strlen(print_buffer));
        exit(errno);
    }

    free(print_buffer);
    print_buffer = NULL;

    free(file_descriptor);
    file_descriptor = NULL;
}

/*
    READING FILE BY WORD BY CHARACTER
    Loop through the file by each character, saving each character in 'word'
    If the character is a space or new line, add the null character to word to signify end of word,
    then add the word to hashmap

    We pass in 'word' to add since the HashBin constructor COPIES the passed in char*.
    Thus, in-place reading of the word works as intended

    Next word will start the index at 0, so each word is saved in 'word' sequentially
*/
void sort_words(int *text, HashMap *hash_map) {
    char *buffer = (char *) malloc(sizeof(char)); // allocating buffer
    char *word = (char *) malloc(MAX_WORD_LEN*sizeof(char)); // in-place current word
    int *char_count = (int *) malloc(sizeof(int)); // current amount of chars in word
    *char_count = 0;

    char *print_buffer = (char *) malloc(50*sizeof(char));
    ssize_t *i = (ssize_t *) malloc(sizeof(ssize_t));

    do {
        *i = read(*text, buffer, 1);

        switch(*i) {
            case -1:
                sprintf(print_buffer, "Error reading file: errno = %i", errno);
                write(STDOUT_FILENO, print_buffer, strlen(print_buffer));
                exit(errno); 
            case 0:
                return; // END OF FILE
        }
        *char_count += *i;

        word[*char_count] = *buffer;

        if(!IS_ALPHANUMERIC(word[*char_count])) {
            word[*char_count] = '\0'; // Terminate word
            add(hash_map, word); // Add word to hashmap
            *char_count = 0; // Start new word
        }
    } while (*char_count != 0);

    free(i);
    i = NULL;

    free(buffer);
    buffer = NULL;

    free(word);
    word = NULL;

    free(char_count);
    char_count = NULL;

    // Why is a char* being passed into a function that takes in a HashBin*?
    // free_bin(print_buffer);
    // print_buffer = NULL;
}

int main(int argc, char *argv[]) {
    int *text = (int *) malloc(sizeof(int)); // File descriptor
    HashMap *hash_map = hashmap(MAP_SIZE);
    char *print_buffer = (char *) malloc(50*sizeof(char));
    char *path = (char *) malloc(50*sizeof(char));

    switch(argc) {
        case 1:
            path = getenv("WORD_FREAK"); 

            if(path != NULL) {
                /* READ FROM ENVIRONMENT VARIABLE */
                *text = open_file(path, O_RDONLY);

                sort_words(text, hash_map); // This is where the magic happens

                close_file(text);
            } else {
                /* READ FROM STDIN */
                sort_words(STDIN_FILENO, hash_map);
            }
            break;
        default:
             /* READ FROM *argv[] */
            for(int i = 1; i < argc; i++) {
                *text = open_file(argv[i], O_RDONLY); // reading only

                sort_words(text, hash_map); // This is wehre the magic happens

                close_file(text);
            }
    }

    free(text);
    text = NULL;

    free(print_buffer);
    print_buffer = NULL;

    free(path);
    path = NULL;
    
    return 0;
}