#include "hashmap.h"
#include <string.h>

HashEntry *hashentry(char *word){ 
    HashEntry *new_entry = (HashEntry *) malloc(sizeof(HashEntry));

    int *len = (int *) malloc(sizeof(int));
    *len = strlen(word);
    new_entry->word = (char *) malloc(((*len)+1)*sizeof(char));
    strncpy(new_entry->word, word, *len+1);

    *(new_entry->frequency) = 1;

    free(len);
    len = NULL;

    return new_entry;
}

int *hash(char *word) {
    
    return 0;
}

int add(int map_len, HashEntry *hash_map[map_len], char *word) {
    const int jump = 1;
    int *index = hash(word);
    
    while(1) {
        if(hash_map[*index] == NULL) {
            hash_map[*index] = hashentry(word);
            break;
        } else if(strncmp(hash_map[*index]->word, word) == 0) {
            hash_map[*index]->frequency++;
            break;
        } else {
            (*index) += jump;
        }
    }

    free(index);
    index = NULL;

    return 0;
}