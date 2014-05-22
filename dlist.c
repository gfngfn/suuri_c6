#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"
#include "hash.h"

dlobj *dlobj_new(kvpair *kvp) {
	dlobj *po;

	mymalloc(po, dlobj, 1);
	po->next = INDEPENDENT_DLOBJ;
	po->prev = INDEPENDENT_DLOBJ;
	po->x = kvp;

	return po;
}

dlist *dlist_new() {
	dlist *pl;
	dlobj *headofpl;
	kvpair *kvp;

	kvp = kvpair_new("\0", "\0");
	headofpl = dlobj_new(kvp);
	headofpl->next = headofpl;
	headofpl->prev = headofpl;

	mymalloc(pl, dlist, 1);
	pl->head = headofpl;

	return pl;
}

dlobj *dlist_search(dlist *psbjl, kvpair *kvp) {
	dlobj *po;

	po = psbjl->head->next;
	while(po != psbjl->head) {
		if(kvpair_cmp(po->x, kvp) == SAME_KEY) {
			return po;
		} else {
			po = po->next;
		}
	}
	return DLOBJ_NOT_FOUND;
}

void dlist_insert(dlist *pl, dlobj *pnewo) {

	pnewo->next = pl->head->next;
	pnewo->prev = pl->head;
	pl->head->next->prev = pnewo;
	pl->head->next = pnewo;

	return;
}

void dlist_append(dlist *pl, dlobj *pnewo) {

	pnewo->next = pl->head;
	pnewo->prev = pl->head->prev;
	pl->head->prev->next = pnewo;
	pl->head->prev = pnewo;

	return;
}

void dlist_delete(dlobj *pdltdo) {

	pdltdo->prev->next = pdltdo->next;
	pdltdo->next->prev = pdltdo->prev;
	pdltdo->prev = INDEPENDENT_DLOBJ;
	pdltdo->next = INDEPENDENT_DLOBJ;

	return;
}

void dlist_free(dlist *pl) {
	dlobj *po, *ponx;

	po = pl->head->next;
	while(po != pl->head) {
		ponx = po->next;
		free(po);
		po = ponx;
	}
	free(pl->head);
	free(pl);

	return;
}

