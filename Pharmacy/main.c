#include "ui.h"
#include <stdio.h>
#include <crtdbg.h>

int main() {

	Ui* ui = ui_create();

	ui_start(ui);

	ui_destroy(ui);

	int val = _CrtDumpMemoryLeaks();
	if (val)
		printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!\nMEMORY LEAKS FOUND");
	else printf("\n\nMemory is correctly deallocated.");
}
