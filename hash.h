#ifndef MyStandardDefinition
#define MyStandardDefinition 0
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define TRU 1
#define FLS 0
typedef int BOOL;
#define mymalloc(p, type, n) {\
	p = (type*)malloc(sizeof(type) * n);\
	if(p == NULL) {\
		printf("[mymalloc] not enough memories\n");\
		exit(EXIT_FAILURE);\
	}\
}
#define myfopen(fp, fn, m) {\
	fp = fopen(fn, m);\
	if(fp == NULL) {\
		printf("[myfopen] cannot open file '%s'\n", fn);\
		exit(EXIT_FAILURE);\
	}\
}
#define SAME_STRING 0
#endif

/*---- constants used in functions ----*/
#define SAME_KEY 0
#define DIFFERENT_KEY 1
#define HASHKEY_MAX 128
#define VALUE_MAX 4096

typedef char* hashkey_t;
typedef char* value_t;

typedef struct kvpair_ {
	hashkey_t key;
	value_t value;
} kvpair;

typedef struct hash_ {
	int stock;
	int size;
	dlist **root;
} hash;

/*---- begin prototype declaration of the functions in 'hash.c' ----*/
static int hash_func(hashkey_t);
int kvpair_cmp(kvpair*, kvpair*);
void kvpair_free(kvpair*);
void kvpair_print(kvpair*);

kvpair* kvpair_new(hashkey_t, value_t);

hash *hash_new(int);
dlobj *hash_search(hash*, hashkey_t);
void hash_insert(hash*, hashkey_t, value_t);
void hash_delete(hash*, dlobj*);
/*---- end prototype declaration ----*/

