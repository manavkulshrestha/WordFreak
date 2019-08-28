#ifndef HASHBIN_H_
#define HASHBIN_H_

typedef struct HashBin {
    char *word;
    int *frequency;
    struct HashBin *link;
} HashBin;

HashBin *hashbin(char *word, int frequency);
void free_bin(HashBin *bin);

void write_with_error_check(char *buffer);

#endif