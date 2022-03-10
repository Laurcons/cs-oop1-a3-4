#include "controller.h"
#include "repository.h"
#include <string.h>

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

int medc_find_str(MedController* medc, char* name, Vector* out) {
	char* lowerSource = NULL;

	Vector* all = medr_get_all(medc->repo);
	int isEmpty = strlen(name) == 0;
	for (int i = 0; i < vect_len(all); i++) {
		Medicine* med = (Medicine*)vect_get_at(all, i);

		int len = strlen(med->name);
		// thanks to Stefania for this fix
		if (len < 0)
			return 1;
		// create a buffer to store the lowercase string in
		lowerSource = (char*)malloc((len + 1) * sizeof(char));
		if (lowerSource == NULL) {
			return 2;
		}
		for (int i = 0; i < len; i++) {
			lowerSource[i] = med->name[i];
			if (med->name[i] >= 'A' && med->name[i] <= 'Z')
				lowerSource[i] += 32;
		}
		lowerSource[len] = '\0';

		if (strstr(lowerSource, name) != NULL || isEmpty) {
			// found! add to out vector
			vect_append(out, med);
		}
		free(lowerSource);
	}
	return 0;
}

Medicine* medc_update_start(MedController* medc, char* name, char* conc) {
	Medicine* med = medr_find(medc->repo, name, conc, NULL);
	return med;
}

int medc_update_end(MedController* medc, Medicine* med, char* name, char* conc, int quantity, int price) {
	// try pre-allocating the new character arrays
	char* newName = (char*)malloc(strlen(name) * sizeof(char) + 1);
	if (newName == NULL)
		return 1;
	char* newConc = (char*)malloc(strlen(conc) * sizeof(char) + 1);
	if (newConc == NULL) {
		free(newName);
		return 1;
	}
	// de-allocate old char arrays
	free(med->name);
	free(med->conc);
	// put new arrays in place
	med->name = newName;
	med->conc = newConc;
	
	// copy new values
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