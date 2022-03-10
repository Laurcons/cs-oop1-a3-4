#pragma once
#include "repository.h"

typedef struct {
	MedRepo* repo;
} MedController;

MedController* medc_create();
void medc_destroy(MedController*);

/* Adds a medicine to the repo. Returns 0 if new entry was created, 1 if it was merged
with an existing entity. */
int medc_add(MedController*, char*, char*, int, int);
Medicine* medc_update_start(MedController*, char*, char*);
int medc_update_end(MedController*, Medicine*, char*, char*, int, int);
/* Tries to remove a medicine. Returns 0 if successful, 1 if not found. */
int medc_remove(MedController*, char*, char*);
int medc_find_str(MedController*, char*, Vector*);
Vector* medc_get_all(MedController*);