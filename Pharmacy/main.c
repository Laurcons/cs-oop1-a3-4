#include "base.h"
#include "ui.h"
#include "test.h"

int main() {

	test_all();

	Ui* ui = ui_create();
	ui_start(ui);
	ui_destroy(ui);

	int val = _CrtDumpMemoryLeaks();
	if (val)
		printf("\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!\nMEMORY LEAKS FOUND");
	else printf("\n\nMemory is correctly deallocated.");
}
