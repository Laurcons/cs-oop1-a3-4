#pragma once
#include <stdlib.h>

typedef void (*VectDestroyFunc)(void*);
typedef int (*VectSortingFunc)(void*, void*);

typedef struct {
	void** elem;
	int len;
	int cap;
	VectDestroyFunc destroy_func;
} Vector;

/* Creates a vector with default parameters. */
Vector* vect_create();
/* Creates a vector using custom parameters: initial capacity, vector destroy function.
If the VectDestroyFunc is NULL, freeing will NOT occur. If you want usual freeing, use the
'free' function from stdlib.h */
Vector* vect_create_ex(int, VectDestroyFunc);
/* Frees a vector. */
void vect_destroy(Vector*);
/* Appends an element to the end of the vector. Returns error. */
int vect_append(Vector*, void*);
/* Gets the element from a position. Returns element or NULL on error. */
void* vect_get_at(Vector*, int);
/* Sets the element from a position. Position must exist. Returns error. */
int vect_set_at(Vector*, int, void*);
/* Returns the length of the vector. */
int vect_len(Vector*);
/* Sort an array using a predicate. */
void vect_sort(Vector*, VectSortingFunc);