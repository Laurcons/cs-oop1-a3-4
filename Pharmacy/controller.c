#include "controller.h"
#include "repository.h"

MedController* medc_create() {
	MedController* medc = malloc(sizeof(MedController));
	if (medc == NULL)
		return NULL;
	medc->repo = medr_create();
	if (medc->repo == NULL) {
		free(medc);
		return NULL;
	}
	return medc;
}

void medc_destroy(MedController* medc) {
	medr_destroy(medc->repo);
	free(medc);
}

int medc_add(MedController* medc, char* name, char* conc, int quantity, int price) {

	Medicine* med = NULL;
	int ret = 0;

	// find existing medicine or create one with quantity zero
	Medicine* existingMed = medr_find(medc->repo, name, conc, NULL);
	if (existingMed) {
		med = existingMed;
		ret = 1;
	} else {
		med = med_create(name, conc, 0, price);
		medr_add(medc->repo, med);
		ret = 0;
	}

	// increase quantity
	med->quantity += quantity;

	return ret;
}

void medc_find_str(MedController* medc, char* name, Vector* out) {
	Vector* all = medr_get_all(medc->repo);
	int isEmpty = strlen(name) == 0;
	for (int i = 0; i < vect_len(all); i++) {
		Medicine* med = (Medicine*)vect_get_at(all, i);

		if (strstr(med->name, name) != NULL || isEmpty) {
			// found! add to out vector
			vect_append(out, med);
		}
	}
}

Medicine* medc_update_start(MedController* medc, char* name, char* conc) {
	Medicine* med = medr_find(medc->repo, name, conc, NULL);
	return med;
}

int medc_update_end(MedController* medc, Medicine* med, char* name, char* conc, int quantity, int price) {
	// will cause unexpected behaviour when memory allocations fail
	free(med->name);
	free(med->conc);

	med->name = (char*)malloc(strlen(name) * sizeof(char) + 1);
	if (med->name == NULL) return 1;
	med->conc = (char*)malloc(strlen(conc) * sizeof(char) + 1);
	if (med->conc == NULL) return 1;

	strcpy(med->name, name);
	strcpy(med->conc, conc);
	med->quantity = quantity;
	med->price = price;

	return 0;
}

int medc_remove(MedController* medc, char* name, char* conc) {
	Medicine* med = medr_find(medc->repo, name, conc, NULL);
	if (med == NULL)
		return 1;
	medr_delete(medc->repo, med);
	return 0;
}

Vector* medc_get_all(MedController* medc) {
	return medr_get_all(medc->repo);
}