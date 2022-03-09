#pragma once
#include <stdlib.h>
#include <string.h>

typedef struct {
	char* name;
	char* conc;
	int quantity;
	int price;
} Medicine;

/* Creates a medicine. Params are in order: name, concentration, quantity, price. */
Medicine* med_create(char*, char*, int, int);
/* Frees a medicine from memory. */
void med_destroy(Medicine*);