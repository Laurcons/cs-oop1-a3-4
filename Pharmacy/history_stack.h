#pragma once
#include "vector.h"

typedef struct {
	Vector* elem;
} HistoryStack;

HistoryStack* hstk_create();
void hstk_destroy(HistoryStack*);

void hstk_push(HistoryStack*, Vector*);
Vector* hstk_pop(HistoryStack*);
