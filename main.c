#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dlist.h"
#include "hash.h"

#define MAIN_HASH_SIZE 1024

int main(int argc, char *argv[]) {
	hash *main_hash;
	char cmdstr[HASHKEY_MAX];
	dlobj *finding;

	if(argc != 2) {
		printf("[main] wrong number of arguments\n");
		return EXIT_FAILURE;
	} else {

		main_hash = hash_new(MAIN_HASH_SIZE);
		hash_load(main_hash, argv[1]);

		printf("--------------------------------\n");
		printf("| The DICTIONARY on HASH by 03-140596\n");
		printf("| (MAIN_HASH_SIZE: %d)\n", MAIN_HASH_SIZE);
		printf("| (HASHKEY_MAX: %d)\n", HASHKEY_MAX);
		printf("| (VALUE_MAX: %d)\n", VALUE_MAX);
		printf("| type word to refer the explanation of it\n");
		printf("| type '*' to quit\n");
		printf("--------------------------------\n");
		printf("| loaded dictionary: '%s'\n", argv[1]);
		printf("| number of contents: %d\n", main_hash->stock);
		printf("--------------------------------\n");
		printf("> ");
		fgets(cmdstr, HASHKEY_MAX, stdin);
		if(strchr(cmdstr, '\n') != NULL) { cmdstr[strlen(cmdstr)-1] = '\0'; }

		while(strcmp(cmdstr, "*") != SAME_STRING) {
			finding = hash_search(main_hash, cmdstr);
			if(finding == DLOBJ_NOT_FOUND) {
				printf("'%s' not found in the dictionary\n", cmdstr);
			} else {
				printf("%s\n", finding->x->value);
			}
			printf("> ");
			fgets(cmdstr, HASHKEY_MAX, stdin);
			if(strchr(cmdstr, '\n') != NULL) { cmdstr[strlen(cmdstr)-1] = '\0'; }
		}
		printf("--------------------------------\n");

		return EXIT_SUCCESS;
	}
}

