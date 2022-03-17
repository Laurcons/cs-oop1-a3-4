#include "base.h"
#include "test.h"
#include "controller.h"
#include "history_stack.h"

#define assert(expression) !!(expression) || printf("Assertion failed in %s at line %d!\n\n", __FILE__, __LINE__)

int* alloc_int(int val) {
	int* p = malloc(sizeof(int));
	*p = val;
	return p;
}

void test_vector() {
	Vector* v = vect_create_ex(3, &free);
	assert(v->cap == 3);
	assert(vect_len(v) == 0);
	vect_append(v, alloc_int(5));
	vect_append(v, alloc_int(10));
	assert(vect_len(v) == 2);
	vect_append(v, alloc_int(15));
	vect_append(v, alloc_int(20));
	assert(vect_len(v) == 4);
	int* p = vect_pop(v);
	free(p);
	assert(vect_len(v) == 3);
	vect_set_at(v, 0, alloc_int(6));
	p = vect_get_at(v, 0);
	assert(*p == 6);

	vect_destroy(v);
}

void test_repository() {
	MedRepo* m = medr_create();

	medr_add(m, med_create("Med1", "Conc1", 11, 11));
	medr_add(m, med_create("Med2", "Conc2", 12, 12));
	medr_add(m, med_create("Med3", "Conc3", 13, 13));
	medr_add(m, med_create("Med4", "Conc4", 14, 14));
	medr_add(m, med_create("Med5", "Conc5", 15, 15));

	assert(medr_len(m) == 5);

	int pos;
	Medicine* med = medr_find(m, "Med3", "Conc3", &pos);
	assert(med->quantity == 13);
	assert(pos == 2);

	assert(vect_len(medr_get_all(m)) == 5);

	medr_delete(m, med);
	medr_delete_at(m, 2);
	assert(medr_len(m) == 3);

	med = vect_get_at(medr_get_all(m), 2);
	assert(med->quantity == 15);

	medr_destroy(m);
}

void test_history_stack() {
	HistoryStack* stk = hstk_create();

	Vector* v1 = vect_create();
	vect_append(v1, alloc_int(5));

	Vector* v2 = vect_create();
	vect_append(v2, alloc_int(10));

	hstk_push(stk, v1);
	hstk_push(stk, v2);

	Vector* vx = hstk_pop(stk);
	assert(v2 == vx);
	vect_destroy(vx);

	hstk_destroy(stk);
}

void test_all() {
	test_vector();
	test_repository();
	test_history_stack();
	int res = _CrtDumpMemoryLeaks();
	assert(res == 0);
}