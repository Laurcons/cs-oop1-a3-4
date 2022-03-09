#include "vector.h"

void defaultDestroy(void* elem) {
	free(elem);
}

void noDestroy(void* elem) {
	// do nothing
}

Vector* vect_create() {
	VectDestroyFunc func = &defaultDestroy;
	return vect_create_ex(3, func);
}

void vect_destroy(Vector* arr) {
	for (int i = 0; i < arr->len; i++) {
		arr->destroy_func(arr->elem[i]);
	}
	free(arr->elem);
	free(arr);
}

Vector* vect_create_ex(int capacity, VectDestroyFunc destroyFunc) {
	Vector* arr = malloc(sizeof(Vector));

	if (arr == NULL)
		return NULL;

	arr->cap = capacity;
	arr->len = 0;
	arr->elem = malloc(capacity * sizeof(void*));
	arr->destroy_func = destroyFunc != NULL ? destroyFunc : &noDestroy;

	if (arr->elem == NULL) {
		free(arr);
		return NULL;
	}

	return arr;
}

int vect_append(Vector* arr, void* el) {
	void* newp = NULL;
	// if we've reached capacity, reallocate
	if (arr->len == arr->cap) {
		arr->cap *= 2;
		newp = realloc(arr->elem, arr->cap * sizeof(void*));
		if (newp == NULL)
			return 1;
		arr->elem = newp;
	}
	// append normally
	arr->elem[arr->len] = el;
	arr->len++;
	return 0;
}

void* vect_get_at(Vector* arr, int pos) {
	if (pos < 0 || pos >= arr->len)
		return NULL;
	return arr->elem[pos];
}

int vect_set_at(Vector* arr, int pos, void* el) {
	if (pos < 0 || pos >= arr->len)
		return 1;
	arr->elem[pos] = el;
	return 0;
}

int vect_len(Vector* arr) {
	return arr->len;
}

void vect_sort(Vector* arr, VectSortingFunc compare) {
	// just do something that works...
	int hadChanges = 1;
	while (1) {
		hadChanges = 0;
		for (int i = 0; i < arr->len - 1; i++) {
			void* first = arr->elem[i];
			void* second = arr->elem[i + 1];
			int cmp = compare(first, second);
			if (cmp < 0) {
				// switch
				hadChanges = 1;
				arr->elem[i] = second;
				arr->elem[i + 1] = first;
			}
		}
		if (hadChanges == 0)
			break;
	}
}
