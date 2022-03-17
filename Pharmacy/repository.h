#pragma once
#include "domain.h"
#include "vector.h"

typedef struct {
	Vector* vector;
} MedRepo;

/* Creates a MedRepo */
MedRepo* medr_create();
/* Destroys a MedRepo */
void medr_destroy(MedRepo*);

/* Adds a medicine to the repo. */
void medr_add(MedRepo*, Medicine*);
/* Searches a medicine in the repo by its name and concentration. If the int* is not NULL,
the position of the medicine in the repo will be returned in it. Returns the Medicine or
NULL if not found. */
Medicine* medr_find(MedRepo*, char*, char*, int*);
/* Retrieves the Medicine vector. */
Vector* medr_get_all(MedRepo*);
/* Retrieves the count of Medicines in the repo. */
int medr_len(MedRepo*);
/* Removes (and deallocates) a medicine at position. */
void medr_delete_at(MedRepo*, int);
/* Removes (and deallocates) a specific medicine. */
void medr_delete(MedRepo*, Medicine*);
/* Removes all elements from the repo. */
void medr_clear(MedRepo*);