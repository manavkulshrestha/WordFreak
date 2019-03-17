#include "hashbin.h"
#include <string.h>
#include <stdlib.h>

/* CONSTRUCTOR */
HashBin *hashbin(char *word, int frequency){ 
    HashBin *new_bin = (HashBin *) malloc(sizeof(HashBin));

    int *len = (int *) malloc(sizeof(int));
    *len = strlen(word);
    new_bin->word = (char *) malloc(((*len)+1)*sizeof(char));
    strncpy(new_bin->word, word, *len+1);

    *(new_bin->frequency) = frequency;

    new_bin->link = NULL;

    free(len);
    len = NULL;

    return new_bin;
}

/*
    Arguments:
        const void *a - First object to compare.
        const void *b - Second object to compare.

    Description:
        Compares the two objects provided (a and b) and returns an int representing the result.
        The comparision is used to sort in descending order based on frequency.
        Note that NULL is bigger than everything else. 

    Returns:
        int result = {
            (result > 0)    if a < b
            (result == 0)   if a == b
            (result < 0)    if a > b
        }
*/
int reverse_compare_bin(const void *a, const void *b) {
    if(a == NULL)
        return 1;
    if(b == NULL)
        return -1;
    return *(((HashBin *)b)->frequency)-*(((HashBin *)a)->frequency);
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
}