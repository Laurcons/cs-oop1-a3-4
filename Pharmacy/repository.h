#pragma once
#include "domain.h"
#include "vector.h"
#include <string.h>

/*
	A repository of medicines. DO NOT MODIFY DIRECTLY.
*/
typedef struct {
	Vector* vector;
} MedRepo;

MedRepo* medr_create();
void medr_destroy(MedRepo*);

void medr_add(MedRepo*, Medicine*);
Medicine* medr_find(MedRepo*, char*, char*, int*);
Vector* medr_get_all(MedRepo*);
int medr_len(MedRepo*);
void medr_delete_at(MedRepo*, int);
void medr_delete(MedRepo*, Medicine*);