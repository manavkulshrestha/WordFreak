#include <stdio.h> // sprintf
#include <sys/stat.h> // open
#include <unistd.h>  // POSIX NAMES and read
#include <fcntl.h> // open flags
#include <stdlib.h> // for malloc
#include <errno.h>
#include <string.h>
#include "hashbin.h"
#include "hashmap.h"

#define MAX_WORD_LEN 30
#define MAP_SIZE 5000

/*
    Arguments:
        char c - character to check.

    Description:
        Checks whether character provided is alpha numeric.

    Returns:
        1   if c is alphanumeric.
        0   if c is not alphanumeric.
*/
int is_alpha(char c) {
    return (((c)>='a' && (c) <= 'z') || ((c)>='A' && (c) <= 'Z') || ((c)>='0' && (c) <= '9'));
}

/*
    Arguments:
        char *file_name - string representing the file.
        int flags - flags representing what mode to open file in. Same as open().

    Description:
        Opens file represented by file_name and exits with errno if open() fails
        and returns pointer representing the file descriptor.

    Returns:
        int *text - int pointer representing the file descriptor.
*/
int *open_file(char *file_name, int flags) {
    int *text = (int *) malloc(sizeof(int)); // File descriptor
    if(text == NULL) {
        exit(-1);
    }
    
    *text = open(file_name, flags);
    
    if(*text == -1) {
        char *print_buffer = (char *) malloc(100*sizeof(char)); 

        sprintf(print_buffer, "Error reading file: errno = %i", errno);
        write_with_error_check(print_buffer);

        free(print_buffer);
        print_buffer = NULL;

        exit(errno);
    }

    return text;
}

/*
    Arguments:
        int *text - int pointer representing a file descriptor.

    Description:
        Closes the file represented by the provided file descriptor, exits with
        errno if close() fails.
*/
void close_file(int *text) {
    char *print_buffer = (char *) malloc(100*sizeof(char));

    if(close(*text) == -1) {  // closing file
        sprintf(print_buffer, "Error closing file: errno = %i", errno);
        write_with_error_check(print_buffer);
        exit(errno);
    }

    free(print_buffer);
    print_buffer = NULL;

    free(text);
    text = NULL;
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
    if(buffer == NULL) {
        exit(-1);
    }

    char *word = (char *) malloc(MAX_WORD_LEN*sizeof(char)); // in-place current word
    if(word == NULL) {
        exit(-1);
    }

    int *char_count = (int *) malloc(sizeof(int)); // current amount of chars in word
    if(char_count == NULL) {
        exit(-1);
    }
    *char_count = 0;

    char *print_buffer = (char *) malloc(100*sizeof(char));
    if(print_buffer == NULL) {
        exit(-1);
    }
    ssize_t *i = (ssize_t *) malloc(sizeof(ssize_t));
    if(i == NULL) {
        exit(-1);
    }
    *i = 0;

    do {
        *i = read(*text, buffer, 1);

        switch(*i) {
            case -1:
                sprintf(print_buffer, "Error reading file: errno = %i", errno);
                write_with_error_check(print_buffer);
                exit(errno); 
            case 0:
                return; // END OF FILE
        }
        
        word[*char_count] = *buffer;
        (*char_count)++;

        if(!is_alpha(word[*char_count-1])) {
            word[*char_count-1] = '\0'; // Terminate word
            if(is_alpha(word[0]))  // Make sure detected word isn't false
                add(hash_map, word); // Add word to hashmap
            

            *char_count = 0; // Start new word
        }
    } while (1);

    free(i);
    i = NULL;

    free(buffer);
    buffer = NULL;

    free(word);
    word = NULL;

    free(char_count);
    char_count = NULL;

    free(print_buffer);
    print_buffer = NULL;
}

int main(int argc, char *argv[]) {
    int *text = (int *) malloc(sizeof(int)); // File descriptor
    if(text == NULL) {
        exit(-1);
    }

    HashMap *hash_map = hashmap(MAP_SIZE);
    char *print_buffer = (char *) malloc(100*sizeof(char));
    if(print_buffer == NULL) {
        exit(-1);
    }

    switch(argc) {
        case 1:
            ;char *path = (char *) malloc(100*sizeof(char));
            if(path == NULL) {
                exit(-1);
            }
            path = getenv("WORD_FREAK"); 

            if(path != NULL) {
                /* READ FROM ENVIRONMENT VARIABLE */
                text = open_file(path, O_RDONLY);

                sort_words(text, hash_map); // This is where the magic happens

                close_file(text);
            } else {
                /* READ FROM STDIN */
                *text = STDIN_FILENO;

                sort_words(text, hash_map);

                close_file(text);
            }
            break;
        default:
             /* READ FROM *argv[] */
            for(int i = 1; i < argc; i++) {
                text = open_file(argv[i], O_RDONLY); // reading only

                sort_words(text, hash_map); // This is wehre the magic happens

                close_file(text);
            }
    }

	print_map("%-15s:%5i\n", hash_map);

    free(print_buffer);
    print_buffer = NULL;

    free_map(hash_map);
    hash_map = NULL;

    return 0;
}