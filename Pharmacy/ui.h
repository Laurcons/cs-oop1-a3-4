#pragma once
#include "controller.h"

typedef struct {
	MedController* medc;
} Ui;

Ui* ui_create();
void ui_destroy(Ui*);

void ui_start(Ui*);