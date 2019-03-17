#include <stdio.h> // printf
#include <sys/stat.h> // open
#include <unistd.h>  // POSIX NAMES and read
#include <fcntl.h> // open flags
#include <stdlib.h> // for malloc
#include <errno.h>
#include "hashbin.h"
#include "hashmap.h"

#define MAX_WORD_LEN 30
// #define MAP_LEN 131 // Arbitrary prime number, will be changed later if more capacity is needed
#define MAP_SIZE 5000

/*
MAIN FUNCTION REVAMP (remove io functions etc)
HASH IMPLMENTATION (deal with hash collisions using probing instead of chaining?)
HASH FUNCTION (make it better)
*/

int main(int argc, char *argv[], char *envp[]) {
    HashMap *hash_map = hashmap(MAP_SIZE);

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

        char *buffer = (char *) malloc(sizeof(char)); // allocating buffer
        char *word = (char *) malloc(MAX_WORD_LEN*sizeof(char)); 
        int *char_count = (int *) malloc(sizeof(int));
        *char_count = 0;

        /*
            READING FILE BY WORD BY CHARACTER
            Loop through the file by each character, saving each character in 'word'
            If the character is a space or new line, add the null character to word to signify end of word,
            then add the word to hashmap

            We pass in 'word' to add since the HashBin constructor COPIES the passed in char*.
            Thus, in-place reading of the word works as intended

            Next word will start the index at 0, so each word is saved in 'word' sequentially
        */
        for (*char_count += read(*text, buffer, 1); *char_count != 0;) {
            word[*char_count] = buffer;
            if(word[*char_count] == ' ' || word[*char_count] == '\n') {
                word[*char_count] == '\0'; // Terminate word
                add(hash_map, word); // Add word to hashmap
                *char_count = 0; // Start new word
            }
        }


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