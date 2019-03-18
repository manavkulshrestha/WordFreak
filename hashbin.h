#ifndef HASHBIN_H_
#define HASHBIN_H_

typedef struct HashBin {
    char *word;
    int *frequency;
} HashBin;

HashBin *hashbin(char *word, int frequency);
int reverse_compare_bin(const void *a, const void *b);
void free_bin(HashBin *bin);

#endif