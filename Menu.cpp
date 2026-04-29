#include "Header.h"
#include <conio.h>


void menu(int select) {
	system("cls");
	std::string options[] = {"First", "Last", "Next", "Prev", "Print playlist", "Repeat track", "Repeat playlist", "New track", "Delete track"};

	for (int i = 0; i < 9; i++) { 
		if (i == select)
			std::cout << "-> " << options[i] << std::endl;
		else
			std::cout << options[i] << std::endl;
	}
}


int move(int& select) { 
	int key = _getch();
	if (key == 224) { 
		key = _getch();
		if (key == 72) 
			select = (select > 0) ? select - 1 : 8;
		if (key == 80) 
			select = (select < 8) ? select + 1 : 0;
		return 0;
	}
	else if (key == 13)
		return 1;
	return 0;
}


void menu_selector() {
	int select = 0;

	while (1) {
		menu(select);
		if (move(select)) {
			switch (select) {
			case 0:
				// First
				break;
			case 1:
				// Last
				break;
			case 2:
				// Next
				break;
			case 3:
				// Prev
				break;
			case 4:
				// Print playlist
				break;
			case 5:
				// Repeat track
				break;
			case 6:
				// Repeat playlist
				break;
			case 7:
				// New track
				break;
			case 8:
				// Delete track
				break;
			}
		}
	}
}