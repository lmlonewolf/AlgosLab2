#include "Header.h"
#include <conio.h>


enum class Page {
	PLAYLIST,
	TRACK,
	REP_TR,
	REP_PL,
	NEW,
	DEL,
	NOTHING
};

unsigned short menu_size = 8;
Page page = Page::NOTHING;



void menu(int select, Playlist& PL, Node* current) {
	system("cls");
	std::string options[] = {"Print playlist", "Play", "Next", "Prev", "Repeat track", "Repeat playlist", "New track", "Delete track"};
	for (int i = 0; i < menu_size; i++) {
		if (i == select)
			std::cout << "-> " << options[i] << std::endl;
		else
			std::cout << options[i] << std::endl;
	}

	switch (page) {
	case Page::PLAYLIST:
		PL.print();
		break;
	case Page::TRACK:
		current->data->print();
		break;
	case Page::REP_TR:
		if (PL.repeat_tr)
			std::cout << std::endl << "The TRACK will BE repeated.";
		else
			std::cout << std::endl << "The TRACK will NOT repeat itself.";
		break;
	case Page::REP_PL:
		if (PL.repeat_pl)
			std::cout << std::endl << "The PLAYLIST will BE repeated.";
		else
			std::cout << std::endl << "The PLAYLIST will NOT repeat itself.";
		break;
	}
}


void menu_selector(Playlist& PL) {
	int select = 0;
	Node* current = PL.first;
	while (1) {
		menu(select, PL, current);
		if (move(select)) {
			switch (select) {
			case 0:
				// Print playlist
				page = Page::PLAYLIST;
				break;
			case 1:
				// Play
				current = PL.first;
				page = Page::TRACK;
				break;
			case 2:
				// Next
				if (!PL.repeat_tr) {
					if (current->next)
						current = current->next;
					else if (PL.repeat_pl)
						current = PL.first;
				}
				page = Page::TRACK;
				break;
			case 3:
				// Prev
				if (!PL.repeat_tr) {
					if (current->prev)
						current = current->prev;
					else if (PL.repeat_pl)
						current = PL.last;
				}
				page = Page::TRACK;
				break;
			case 4:
				// Repeat track
				PL.repeat_tr = !PL.repeat_tr;
				page = Page::REP_TR;
				break;
			case 5:
				// Repeat playlist
				PL.repeat_pl = !PL.repeat_pl;
				page = Page::REP_PL;
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