#include "BUS.h"

BUS rv_bus[MAX_TIME] = { {"10:30"}, {"12:30"}, {"14:30"}, {"16:30"}, {"18:30"} };

int main()
{
	char menu;
	system("mode con cols=60 lines=30");
	read_reservation();

	show_login_menu();

	while (1) {
		main_menu();
		menu = sel_menu();
		run_menu(menu);
	}

	return 0;
}