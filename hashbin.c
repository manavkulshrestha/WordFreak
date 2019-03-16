#include "hashbin.h"
#include <string.h>
#include <stdlib.h>

HashBin *hashbin(char *word){ 
    HashBin *new_bin = (HashBin *) malloc(sizeof(HashBin));

    int *len = (int *) malloc(sizeof(int));
    *len = strlen(word);
    new_bin->word = (char *) malloc(((*len)+1)*sizeof(char));
    strncpy(new_bin->word, word, *len+1);

    *(new_bin->frequency) = 1;

    new_bin->link = NULL;

    free(len);
    len = NULL;

    return new_bin;
}

int compare_bin(const void *a, const void *b) {
    if(a == NULL)
        return -1;
    if(b == NULL)
        return 1;
    return *(((HashBin *)a)->frequency)-*(((HashBin *)b)->frequency);
}

void free_bin(HashBin *bin) {
    if(bin == NULL)
        return;

    free(bin->word);
    bin->word = NULL;

    free(bin->frequency);
    bin->frequency = NULL;

    free_bin(bin->link);
    bin->link = NULL;
}