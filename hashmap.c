#include "hashmap.h"
#include <string.h>

HashEntry *hashentry(char *word){ 
    HashEntry *new_entry = (HashEntry *) malloc(sizeof(HashEntry));

    int *len = (int *) malloc(sizeof(int));
    *len = strlen(word);
    new_entry->word = (char *) malloc(((*len)+1)*sizeof(char));
    strncpy(new_entry->word, word, *len+1);

    *(new_entry->frequency) = 1;

    new_entry->link = NULL

    free(len);
    len = NULL;

    return new_entry;
}

int *hash(char *word) {
    
    return 0;
}

void add(int map_len, HashEntry *hash_map[map_len], char *word) {
    int *index = hash(word);

    if(hash_map[*index] == NULL) {
        hash_map[*index] = hashentry(word);
    } else {
        HashEntry *curr = hash_map[*index];
        while(1) {
            if(strncmp(curr->word, word) == 0)
                (*(curr->frequency))++;
                break;
            else if(curr->link == NULL) {
                curr->link = hashentry(word);
                break;
            } else {
                curr = curr->link;
            }
        }
    }

    free(index);
    index = NULL;

    return 0;
}