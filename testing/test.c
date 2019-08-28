#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "hashmap.h"

typedef struct Test {
	int *a;
} Test;

// Test *test(int a) {
// 	Test *t = malloc(sizeof(Test));

// 	t->
// }

int main(int argc, char **argv, char **envp) {
	// printf("agrv:\n");
	// for(int i=0; i<argc; i++)
	// 	printf("%s\n", argv[i]);

	// printf("\nenvp:\n");
	// for(int i=0; envp[i]; i++)
	// 	printf("%s\n", envp[i]);

	// char *buf = (char *) malloc(100*sizeof(char));

	// ssize_t len = read(STDIN_FILENO, buf, 49);
	// buf[len] = '\0';

	// printf("%s", buf);

	// len = read(STDIN_FILENO, buf, 49);
	// buf[len] = '\0';

	// printf("%s", buf);

	// free(buf);

	HashMap *hm = hashmap(2);

	add(hm, "1");

	printf("HM: \n");
	print_map("%s:\t\t%i\n", hm);
	printf("\n");

	add(hm, "2");

	printf("HM: \n");
	print_map("%s:\t\t%i\n", hm);
	printf("\n");

	add(hm, "3");

	printf("HM: \n");
	print_map("%s:\t\t%i\n", hm);
	printf("\n");

	return 0;
}
