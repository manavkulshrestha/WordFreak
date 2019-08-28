int hash (char *word, int *size) {
    int *intlength = (int *) malloc(sizeof(int));
    *intLength = strlen(word) / 4;

    long *sum = (long *) malloc(sizeof(long));
    *sum = 0;

    char *c = (char *) malloc(strlen(word) * sizeof(char));
    int *i = (int *) malloc(sizeof(int));

    long *mult = (long *) malloc(sizeof(long));

    for (int j = 0; j < intLength; j++) {
        for(*i = j*4; *i < (j*4)+4; *i++)
            c[*i-j*4] = word[*i];
        c[*i] = '\0';
        
        *mult = 1;
        for (int k = 0; k < strlen(c); k++) {
	        sum += c[k] * mult;
	        mult *= 256;
        }
    }

    for(*i = intLength*4; *i < strlen(word); *i++)
        c[*i - (intLength*4)] = word[*i];
    *mult = 1;
    for (int k = 0; k < strlen(c); k++) {
        sum += c[k] * mult;
        mult *= 256;
    }

    return(((sum >= 0) ? sum : -sum) % *size);
}