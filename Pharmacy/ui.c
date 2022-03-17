#include "base.h"
#include "ui.h"
#include <conio.h>

void noFree(void* discard) {}

Ui* ui_create() {
	Ui* ui = (Ui*)malloc(sizeof(Ui));

	if (ui == NULL)
		return NULL;

	ui->medc = medc_create();

	if (ui->medc == NULL) {
		free(ui);
		return NULL;
	}

	medc_set_history_enabled(ui->medc, 0);
	medc_add(ui->medc, "Advil", "100%", 10, 100);
	medc_add(ui->medc, "Xanax", "90%", 23, 200);
	medc_add(ui->medc, "NoSpa", "95%", 27, 300);
	medc_add(ui->medc, "Parasinus", "85%", 23, 100);
	medc_add(ui->medc, "Aspenter", "80%", 25, 150);
	medc_add(ui->medc, "Faringosept", "100%", 16, 160);
	medc_add(ui->medc, "Calcidrin", "95%", 120, 120);
	medc_add(ui->medc, "Fenistil", "80%", 18, 200);
	medc_add(ui->medc, "Colebil", "85%", 26, 250);
	medc_add(ui->medc, "Paracetamol", "55%", 27, 230);
	medc_set_history_enabled(ui->medc, 1);

	return ui;
}

void ui_destroy(Ui* ui) {
	medc_destroy(ui->medc);
	free(ui);
}

void print_menu() {
	printf("Pharmacy Manager 'Smiles Pharma'\n");
	printf("What do you want to do?\n");
	printf("a. Modify medications\n");
	printf("b. Find medications by string\n");
	printf("c. Find medications in short supply\n");
	printf("d. Undo\n");
	printf("e. Redo\n");
	printf("x. Exit\n");
}

void do_suboption_aa(Ui* ui) {
	char *name, *conc;
	int price, quantity;

	name = (char*)malloc(256 * sizeof(char));
	conc = (char*)malloc(256 * sizeof(char));
	if (name == NULL || conc == NULL) {
		name == NULL ? free(name) : 1;
		conc == NULL ? free(conc) : 1;
		printf("Memory error.");
		return;
	}

	printf("Enter a name: ");
	scanf_s("%s", name, 255);

	printf("Enter a concentration: ");
	scanf_s("%s", conc, 255);

	printf("Enter a quantity: ");
	scanf_s("%d", &quantity);

	printf("Enter a price: ");
	scanf_s("%d", &price);

	int ret = medc_add(ui->medc, name, conc, quantity, price);
	if (ret == 1) {
		printf("Medicine already exists, quantities were merged and new price dropped\n");
	}

	free(name);
	free(conc);

	printf("Successfully added.");
}

void do_suboption_ab(Ui* ui) {
	char* oldname, * oldconc;
	char* name, * conc;
	int quantity, price;

	oldname = (char*)malloc(256 * sizeof(char));
	if (oldname == NULL) {
		printf("Memory error.");
		return;
	}
	oldconc = (char*)malloc(256 * sizeof(char));
	if (oldconc == NULL) {
		free(oldname);
		printf("Memory error.");
		return;
	}

	printf("Type the name and concentration of the medicine you want to update.\n");
	printf("Name: ");
	scanf_s("%s", oldname, 255);
	printf("Concentration: ");
	scanf_s("%s", oldconc, 255);

	Medicine* med = medc_update_start(ui->medc, oldname, oldconc);
	free(oldname);
	free(oldconc);
	if (med == NULL) {
		printf("Medicine wasn't found.\n");
		return;
	}

	name = (char*)malloc(256 * sizeof(char));
	conc = (char*)malloc(256 * sizeof(char));
	if (name == NULL || conc == NULL) {
		name == NULL ? free(name) : 1;
		conc == NULL ? free(conc) : 1;
		printf("Memory error.");
		return;
	}

	printf("Enter the new details.\n");
	printf("Enter a name: ");
	scanf_s("%s", name, 255);
	printf("Enter a concentration: ");
	scanf_s("%s", conc, 255);
	printf("Enter a quantity: ");
	scanf_s("%d", &quantity);
	printf("Enter a price: ");
	scanf_s("%d", &price);

	medc_update_end(ui->medc, med, name, conc, quantity, price);

	free(name);
	free(conc);

	printf("Successfully updated.");

}

void do_suboption_ac(Ui* ui) {
	char* name, * conc;

	name = (char*)malloc(256 * sizeof(char));
	conc = (char*)malloc(256 * sizeof(char));
	if (name == NULL || conc == NULL) {
		name == NULL ? free(name) : 1;
		conc == NULL ? free(conc) : 1;
		printf("Memory error.");
		return;
	}

	printf("Enter name: ");
	scanf_s("%s", name, 255);
	printf("Enter concentration: ");
	scanf_s("%s", conc, 255);

	int ret = medc_remove(ui->medc, name, conc);
	free(name);
	free(conc);

	if (ret == 1) {
		printf("Medicine not found.");
		return;
	}
	printf("Successfully deleted.");
}

// kudos to Rapeanu
int medcmp(Medicine* first, Medicine* second) {
	return strcmp(first->name, second->name);
}

void do_option_b(Ui* ui) {
	char* searchStr;
	int res;

	searchStr = (char*)malloc(256 * sizeof(char));
	if (searchStr == NULL) {
		printf("Memory error.");
		return;
	}

	printf("Enter a search string (or - to get all): ");
	scanf_s("%s", searchStr, 255);

	if (strcmp(searchStr, "-") == 0) {
		searchStr[0] = '\0';
	}

	// create a vector with freeing disabled
	Vector* list = vect_create_ex(3, &med_destroy);
	// fill it
	res = medc_find_str(ui->medc, searchStr, list);
	if (res != 0) {
		printf("Memory error.");
		vect_destroy(list);
		return;
	}
	// sort it
	vect_sort(list, &medcmp);

	// print it
	for (int i = 0; i < vect_len(list); i++) {
		Medicine* med = (Medicine*)vect_get_at(list, i);
		printf("\"%s\" %s %dx $%d\n",
			med->name,
			med->conc,
			med->quantity,
			med->price);
	}

	vect_destroy(list);
	free(searchStr);
}

void do_option_a(Ui* ui) {
	printf("What do you want to do?\n");
	printf("a. Add a new medication\n");
	printf("b. Update a medication\n");
	printf("c. Remove a medication\n");
	printf("z. Back\n");
	char opt = _getch();

	switch (opt) {
	case 'a': do_suboption_aa(ui); break;
	case 'b': do_suboption_ab(ui); break;
	case 'c': do_suboption_ac(ui); break;
	}

}

void do_option_c(Ui* ui) {
	int quant = 0, res;

	printf("Enter the quantity treshold: ");
	scanf_s("%d", &quant);

	Vector* out = vect_create_ex(3, &med_destroy);
	res = medc_find_short_supply(ui->medc, quant, out);
	if (res != 0) {
		printf("Memory error.");
		vect_destroy(out);
		return;
	}

	// sort it
	vect_sort(out, &medcmp);

	// print it
	for (int i = 0; i < vect_len(out); i++) {
		Medicine* med = (Medicine*)vect_get_at(out, i);
		printf("\"%s\" %s %dx $%d\n",
			med->name,
			med->conc,
			med->quantity,
			med->price);
	}

	vect_destroy(out);
}

void do_option_d(Ui* ui) {
	int ret = medc_undo(ui->medc);

	if (ret == 1) {
		printf("Nothing to undo.");
	}
	else if (ret == 0) {
		printf("Successfully undone.");
	}
	else {
		printf("Something probably caught fire idk.");
	}
}

void do_option_e(Ui* ui) {
	int ret = medc_redo(ui->medc);

	if (ret == 1) {
		printf("Nothing to redo.");
	}
	else if (ret == 0) {
		printf("Successfully redone.");
	}
	else {
		printf("Something probably caught fire idk.");
	}
}

void ui_start(Ui* ui) {
	char c;

	while (1) {
		print_menu();
		c = _getch();

		if (c == 'x')
			break;

		switch (c) {
		case 'a': do_option_a(ui); break;
		case 'b': do_option_b(ui); break;
		case 'c': do_option_c(ui); break;
		case 'd': do_option_d(ui); break;
		case 'e': do_option_e(ui); break;
		}

		printf("\n\n");
	}
}