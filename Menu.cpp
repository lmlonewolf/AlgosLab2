#include "Header.h"
#include <conio.h>

size_t menu_size = 8;

void menu(int select) {
	system("cls");
	std::string options[] = {"Print playlist", "Play", "Next", "Prev", "Repeat track", "Repeat playlist", "New track", "Delete track"};
	for (int i = 0; i < menu_size; i++) {
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
			select = (select > 0) ? select - 1 : menu_size - 1;
		if (key == 80) 
			select = (select < menu_size - 1) ? select + 1 : 0;
		return 0;
	}
	else if (key == 13)
		return 1;
	return 0;
}


void menu_selector(Playlist& PL) {
	int select = 0;

	while (1) {
		menu(select);
		if (move(select)) {
			switch (select) {
			case 0:
				// Print playlist
				PL.print();
				system("pause");
				break;
			case 1:
				// Play
				break;
			case 2:
				// Next
				break;
			case 3:
				// Prev
				break;
			case 4:
				// Repeat track
				break;
			case 5:
				// Repeat playlist
				break;
			case 6:
				// New track
				break;
			case 7:
				// Delete track
				break;
			}
		}
	}
}