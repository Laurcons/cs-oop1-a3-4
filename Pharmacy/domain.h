#pragma once

typedef struct {
	char* name;
	char* conc;
	int quantity;
	int price;
} Medicine;

/* Creates a medicine. Params are in order: name, concentration, quantity, price. */
Medicine* med_create(char*, char*, int, int);
/* Creates a copy of a medicine. Returns the Medicine or NULL on failure. */
Medicine* med_copy(Medicine*);
/* Frees a medicine from memory. */
void med_destroy(Medicine*);