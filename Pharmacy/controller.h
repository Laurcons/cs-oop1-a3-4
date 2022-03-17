#pragma once
#include "repository.h"
#include "history_stack.h"

typedef struct {
	MedRepo* repo;
	int history_enabled;
	HistoryStack* undo_stack;
	HistoryStack* redo_stack;
} MedController;

/* Creates a MedController. */
MedController* medc_create();
/* Destroys a MedController. */
void medc_destroy(MedController*);

/* Adds a medicine to the repo. Returns 0 if new entry was created, 1 if it was merged
with an existing entity. */
int medc_add(MedController*, char*, char*, int, int);
/* Starts an update procedure. Takes a name and concentration of the entity to be
modified. Returns an object needed to end the operation. */
Medicine* medc_update_start(MedController*, char*, char*);
/* Ends an update procedure. Takes the Medicine* object returned from the start function,
and the new values: name, concentration, quality, price. */
int medc_update_end(MedController*, Medicine*, char*, char*, int, int);
/* Tries to remove a medicine. Returns 0 if successful, 1 if not found. */
int medc_remove(MedController*, char*, char*);
/* Retrieves Medicines matching the string (case insensitive), and copies them into the
Vector*. If the search term is of length zero, all entries will be copied into the Vector. */
int medc_find_str(MedController*, char*, Vector*);
/* Retrieves Medicines that are in short supply, and copies them into the Vector*. Provide
the treshold. */
int medc_find_short_supply(MedController*, int, Vector*);
/* Retrieves the medicines vector from the repository. */
Vector* medc_get_all(MedController*);

void medc_set_history_enabled(MedController*, int);

int medc_undo(MedController*);
int medc_redo(MedController*);