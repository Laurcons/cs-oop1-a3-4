#include "base.h"
#include "repository.h"

MedRepo* medr_create() {
	MedRepo* repo = malloc(sizeof(MedRepo));
	if (repo == NULL) return NULL;

	repo->vector = vect_create_ex(3, &med_destroy);
	if (repo->vector == NULL) return NULL;

	return repo;
}

void medr_destroy(MedRepo* repo) {
	vect_destroy(repo->vector);
	free(repo);
}

void medr_add(MedRepo* medrepo, Medicine* med) {
	vect_append(medrepo->vector, (void*)med);
}

Medicine* medr_find(MedRepo* medrepo, char* name, char* conc, int* position) {
	Medicine* med = NULL;
	Medicine* result = NULL;
	int len = vect_len(medrepo->vector);
	for (int i = 0; i < len; i++) {
		med = (Medicine*)vect_get_at(medrepo->vector, i);
		if ((strcmp(med->name, name) == 0) &&
			(strcmp(med->conc, conc) == 0)) {
			result = med;
			if (position != NULL)
				*position = i;
			break;
		}
	}
	return result;
}

Vector* medr_get_all(MedRepo* medrepo) {
	return medrepo->vector;
}

void medr_delete_at(MedRepo* medrepo, int pos) {
	Medicine* med = (Medicine*)vect_get_at(medrepo->vector, pos);
	// deallocate
	med_destroy(med);
	// rearrange elements
	for (int i = pos; i < vect_len(medrepo->vector) - 1; i++) {
		medrepo->vector->elem[i] = medrepo->vector->elem[i + 1];
	}
	// decrement length
	medrepo->vector->len--;
}

void medr_delete(MedRepo* medrepo, Medicine* med) {
	int position = -1;
	medr_find(medrepo, med->name, med->conc, &position);
	if (position == -1)
		return;
	medr_delete_at(medrepo, position);
}

int medr_len(MedRepo* medrepo) {
	return vect_len(medrepo->vector);
}

void medr_clear(MedRepo* medr) {
	// just reallocate the vector lol idk
	// don't even error handle coz fuck that shit
	vect_destroy(medr->vector);
	medr->vector = vect_create_ex(3, &med_destroy);
}