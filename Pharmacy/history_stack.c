#include "base.h"
#include "history_stack.h"

HistoryStack* hstk_create() {
	HistoryStack* stk = malloc(sizeof(HistoryStack));
	if (stk == NULL)
		return NULL;

	stk->elem = vect_create_ex(3, &vect_destroy);
	if (stk->elem == NULL) {
		free(stk);
		return NULL;
	}

	return stk;
}

void hstk_destroy(HistoryStack* stk) {
	vect_destroy(stk->elem);
	free(stk);
}

void hstk_push(HistoryStack* stk, Vector* snapshot) {
	vect_append(stk->elem, snapshot);
}

Vector* hstk_pop(HistoryStack* stk) {
	return vect_pop(stk->elem);
}
