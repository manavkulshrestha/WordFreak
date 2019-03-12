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

// rudimentory. Feel free to change @Anthony
int *hash(char *word, int map_len) {
    int *code = (int *) malloc(sizeof(int));
    *code = 0;

    for(int i=0; i<strlen(word); i++) {
        *code += (int) word[i];
    }

    return code;
}

void add(int map_len, HashEntry *hash_map[map_len], char *word) {
    int *index = hash(word, map_len);

    if(hash_map[*index] == NULL) {
        hash_map[*index] = hashentry(word);
    } else {
        // dealing with hash collision using linked lists
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

void free_hash_entry(HashEntry *entry) {
    if(entry == NULL)
        return;

    free(entry->word);
    entry->word = NULL;

    free(entry->frequency);
    entry->frequency = NULL

    free_hash_entry(entry->link);
    entry->link = NULL;
}

void free_map(int map_len, HashEntry *hash_map[map_len]) {
    for(int i=0; i<map_len; i++) {
        if(hash_map[i] != NULL) {
            free_hash_entry(hash_map[i]);
            hash_map[i] = NULL;
        }
    }
}