#include <stdio.h> // printf
#include <sys/stat.h> // open
#include <unistd.h>  // POSIX NAMES and read
#include <fcntl.h> // open flags
#include <stdlib.h> // for malloc
#include <errno.h>
#include "hashbin.h"
#include "hashmap.h"

#define IS_WHITESPACE(c) c == ' ' || c == '\n'

#define MAX_WORD_LEN 30
#define MAP_SIZE 5000

/*
    READING FILE BY WORD BY CHARACTER
    Loop through the file by each character, saving each character in 'word'
    If the character is a space or new line, add the null character to word to signify end of word,
    then add the word to hashmap

    We pass in 'word' to add since the HashBin constructor COPIES the passed in char*.
    Thus, in-place reading of the word works as intended

    Next word will start the index at 0, so each word is saved in 'word' sequentially
*/
int freak(int *text, HashMap *hash_map) {
    char *buffer = (char *) malloc(sizeof(char)); // allocating buffer
    char *word = (char *) malloc(MAX_WORD_LEN*sizeof(char)); // in-place current word
    int *char_count = (int *) malloc(sizeof(int)); // current amount of chars in word
    *char_count = 0;

    do {
        
        ssize_t i = read(*text, buffer, 1);
        if(*i == -1) {
            printf("Error reading file: errno = %i\n", errno);
            return errno;
        } else if(*i == 0) {
            return 0;
        }
        *char_count += i;

        word[*char_count] = buffer;

        if(IS_WHITESPACE(word[*char_count])) {
            word[*char_count] == '\0'; // Terminate word
            add(hash_map, word, 1); // Add word to hashmap (with dummy 1 as third parameter because making two different functions to add would be blasphemy)
            *char_count = 0; // Start new word
        }
    } while (*char_count != 0)
}

int main(int argc, char *argv[]) {
    int *text = (int *) malloc(sizeof(int)); // File descriptor
    HashMap *hash_map = hashmap(MAP_SIZE);

    word_freak = getenv("WORD_FREAK"); 
    
    if(argc == 1) {

        /* READ FROM ENVIRONMENT VARIABLE */
        if(word_freak != NULL) {

            *text = open(word_freak, O_RDONLY); // reading only

            if(*text == -1) {
                printf("Error opening file %i: errno = %i\n", i, errno);
                return errno;
            }

            freak(text); // This is where the magic happens

            if(close(*text) == -1) {  // closing file
                printf("Error closing file %i: errno = %i\n", i, errno);
                return errno;
            }
        
        /* READ FROM STDIN PIPE */
        } else {

            

        }

    /* READ FROM COMMAND LINE ARGUMENTS */
    } else {

        if(argc < 2) {
            printf("Not enough arguments. argc = %i", argc);
            return argc;
        }

        // Loop through argv[]
        for(int i = 1; i < argc; i++) {
            *text = open(argv[i], O_RDONLY); // reading only

            if(*text == -1) {
                printf("Error opening file %i: errno = %i\n", i, errno);
                return errno;
            }

            freak(text, hash_map); // This is wehre the magic happens

            if(close(*text) == -1) {  // closing file
                printf("Error closing file %i: errno = %i\n", i, errno);
                return errno;
            }
        }
    }

    free(text);
    text = NULL;

    free(buffer);
    buffer = NULL;

    free(bytes_read);
    bytes_read = NULL;
    
    return 0;
}