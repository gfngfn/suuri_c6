#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dlist.h"
#include "hash.h"

static int hash_func(hashkey_t hkt) {
	int h;

	h = 0;
	while(*hkt != 0) {
		h = h * 101 + tolower(*hkt++);
	}

	return abs(h);
}

int kvpair_cmp(kvpair *kvpa, kvpair *kvpb) {
	//printf("(kvpair_cmp) %s <-> %s\n", kvpa->key, kvpb->key);//[test]
	if(strcmp(kvpa->key, kvpb->key) == SAME_STRING) {
		return SAME_KEY;
	} else {
		return DIFFERENT_KEY;
	}
}

void kvpair_free(kvpair *kvp) {
	free(kvp->key);
	free(kvp->value);
	free(kvp);

	return;
}

void kvpair_print(kvpair *kvp) {
	printf("(%s, %s)", kvp->key, kvp->value);

	return;
}

kvpair *kvpair_new(hashkey_t hkt, value_t vt) {
	kvpair *kvp;
	hashkey_t newkey;
	value_t newvalue;

	mymalloc(newkey, char, HASHKEY_MAX);
	strcpy(newkey, hkt);
	mymalloc(newvalue, char, VALUE_MAX);
	strcpy(newvalue, vt);
	mymalloc(kvp, kvpair, 1);
	kvp->key = newkey;
	kvp->value = newvalue;

	return kvp;
}

hash *hash_new(int sz) {
	hash *hs;
	dlist **rt;
	int i;

	mymalloc(hs, hash, 1);
	hs->size = sz;
	hs->stock = 0;

	mymalloc(rt, dlist*, sz);
	for(i = 0; i < sz; i++) { rt[i] = dlist_new(); }
	hs->root = rt;

	return hs;
}

dlobj *hash_search(hash *hs, hashkey_t hkt) {
	int sought;
	kvpair *kvp;
	dlobj *po;

	kvp = kvpair_new(hkt, "\0");

	sought = hash_func(hkt) % (hs->size);
	po = dlist_search((hs->root)[sought], kvp);

	free(kvp);
	return po;
}

void hash_insert(hash *hs, hashkey_t hkt, value_t vt) {
	int insrtd;
	kvpair *kvp;
	dlobj *po;

	kvp = kvpair_new(hkt, vt);
	po = dlobj_new(kvp);
	insrtd = hash_func(hkt) % (hs->size);
	dlist_insert((hs->root)[insrtd], po);

	hs->stock += 1;

	return;
}

void hash_delete(hash *hs, dlobj *pdltdo) {

	dlist_delete(pdltdo);
	hs->stock -= 1;

	return;
}

void hash_load(hash *hs, char *filename) {
	FILE *fp;
	char readline[HASHKEY_MAX+VALUE_MAX], readkey[HASHKEY_MAX], readvalue[VALUE_MAX];

	myfopen(fp, filename, "r");
	while(fgets(readline, HASHKEY_MAX+VALUE_MAX, fp) != NULL) {
		sscanf(readline, "%[^\t]\t%[^\n]", readkey, readvalue);
		hash_insert(hs, readkey, readvalue);
	}

	fclose(fp);
	return;
}

void hash_save(hash *hs, char *filename) {
	FILE *fp;
	int i;
	dlobj *po;

	myfopen(fp, filename, "w");
	for(i = 0; i < hs->size; i++) {
		po = (hs->root)[i]->head->next;
		while(po != (hs->root)[i]->head) {
			fprintf(fp, "%s%s\n", po->x->key, po->x->value);
			//printf("%d:[%s][%s]\n", i, po->x->key, po->x->value);
			po = po->next;
		}
	}

	fclose(fp);
	return;
}

