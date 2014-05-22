/*---- constants used in functions ----*/
#define INDEPENDENT_DLOBJ NULL
#define DLOBJ_NOT_FOUND NULL

typedef struct kvpair_ kvpair;

typedef struct dlobj_ {
	struct dlobj_ *next;
	struct dlobj_ *prev;
	kvpair *x;
} dlobj;

typedef struct {
	dlobj *head;
} dlist;

/*---- begin prototype declaration of the functions in 'dlist.c' ----*/
dlobj *dlobj_new(kvpair*);
dlist *dlist_new(void);
dlobj *dlist_search(dlist*, kvpair*);
void dlist_insert(dlist*, dlobj*);
void dlist_append(dlist*, dlobj*);
void dlist_delete(dlobj*);
void dlist_free(dlist*);
/*---- end prototype declaration ----*/

