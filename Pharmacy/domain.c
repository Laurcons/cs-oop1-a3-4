#include "base.h"
#include "domain.h"

Medicine* med_create(char* name, char* concentration, int quantity, int price) {
	Medicine* med = malloc(sizeof(Medicine));
	if (med == NULL)
		return NULL;
	med->name = malloc(strlen(name) * sizeof(char) + 1);
	med->conc = malloc(strlen(concentration) * sizeof(char) + 1);
	if (med->name == NULL || med->conc == NULL) {
		free(med);
		return NULL;
	}
	strcpy(med->name, name);
	strcpy(med->conc, concentration);
	med->quantity = quantity;
	med->price = price;
	return med;
}

Medicine* med_copy(Medicine* med) {
	return med_create(
		med->name,
		med->conc,
		med->quantity,
		med->price
	);
}

void med_destroy(Medicine* med) {
	free(med->conc);
	free(med->name);
	free(med);
}
