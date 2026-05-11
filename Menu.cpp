#include "Header.h"
#include <conio.h>


enum class Page {
	PLAYLIST,
	TRACK,
	REP_TR,
	REP_PL,
	REP_NO,
	SHUFFLE,
	NEW,
	DEL,
	EMPTY,
	NOTHING
};

const std::string options[] = { "Print playlist", "Play", "Next", "Prev", "Repeat track", "Repeat playlist", "Don't repeat", "Shuffle playlist", "New track", "Delete track" };
unsigned short menu_size = 10;
Page page = Page::NOTHING;


void print_selector(int select) {
	for (int i = 0; i < menu_size; i++) {
		if (i == select)
			std::cout << "\033[0;32m->\033[0m " << options[i] << std::endl;
		else
			std::cout << options[i] << std::endl;
	}
}


void menu(int select, Playlist& PL, Node* current) {
	system("cls");
	switch (page) {
	case Page::NOTHING:
		print_selector(select);
		break;

	case Page::PLAYLIST:
		print_selector(select);

		PL.print();
		break;

	case Page::TRACK:
		print_selector(select);

		current->data->print();
		break;

	case Page::REP_TR:
		print_selector(select);

		if (PL.repeat_tr)
			std::cout << std::endl << "TRACK will BE repeated." << std::endl;
		else
			std::cout << std::endl << "TRACK will NOT repeated." << std::endl;
		break;

	case Page::REP_PL:
		print_selector(select);

		if (PL.repeat_pl)
			std::cout << std::endl << "PLAYLIST will BE repeated." << std::endl;
		else
			std::cout << std::endl << "PLAYLIST will NOT repeated." << std::endl;
		break;

	case Page::REP_NO:
		print_selector(select);
		std::cout << std::endl << "Repeat is disabled." << std::endl;
		break;

	case Page::SHUFFLE:
		print_selector(select);

		std::cout << std::endl << "PLAYLIST was SHUFFLED." << std::endl;
		PL.print();
		break;

	case Page::EMPTY:
		print_selector(select);

		std::cout << std::endl << "PLAYLIST is EMPTY." << std::endl;
		break;

	case Page::NEW:
		system("cls");
		std::string name;
		while (true) {
			std::cout << std::endl << "Input track name: " << std::endl;
			if (std::cin.peek() == '\n')
				std::cin.ignore();
			if (std::getline(std::cin, name))
				break;
			std::cout << std::endl << "Input error! Try again." << std::endl;
		}

		unsigned time;
		while (true) {
			std::cout << std::endl << "Input track time: " << std::endl;
			if (std::cin >> time)
				break;
			std::cout << std::endl << "Input error! Try again." << std::endl;
		}

		std::string style;
		while (true) {
			std::cout << std::endl << "Input track style: " << std::endl;
			if (std::cin.peek() == '\n')
				std::cin.ignore();
			if (std::getline(std::cin, style))
				break;
			std::cout << std::endl << "Input error! Try again." << std::endl;
		}

		unsigned short rate;
		while (true) {
			std::cout << std::endl << "Input track rating: " << std::endl;
			if (std::cin >> rate)
				break;
			std::cout << std::endl << "Input error! Try again." << std::endl;
		}

		PL.new_last(new Track(name, time, style, rate));
		system("cls");
		print_selector(select);
		PL.print();
		page = Page::PLAYLIST;
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
				if (PL.first == nullptr)
					page = Page::EMPTY;
				else {
					current = PL.first;
					page = Page::TRACK;
				}
				break;
			case 2:
				// Next
				if (PL.first == nullptr)
					page = Page::EMPTY;
				else {
					if (!PL.repeat_tr) {
						if (current->next)
							current = current->next;
						else if (PL.repeat_pl)
							current = PL.first;
					}
					page = Page::TRACK;
				}
				break;
			case 3:
				// Prev
				if (PL.first == nullptr)
					page = Page::EMPTY;
				else {
					if (!PL.repeat_tr && PL.first) {
						if (current->prev)
							current = current->prev;
						else if (PL.repeat_pl)
							current = PL.last;
					}
					page = Page::TRACK;
				}
				break;
			case 4:
				// Repeat track
				if (PL.first == nullptr)
					page = Page::EMPTY;
				else {
					PL.repeat_tr = !PL.repeat_tr;
					PL.repeat_pl = false;
					page = Page::REP_TR;
				}
				break;
			case 5:
				// Repeat playlist
				if (PL.first == nullptr)
					page = Page::EMPTY;
				else {
					PL.repeat_pl = !PL.repeat_pl;
					PL.repeat_tr = false;
					page = Page::REP_PL;
				}
				break;

			case 6:
				PL.repeat_tr = false;
				PL.repeat_pl = false;
				page = Page::REP_NO;
				break;
			case 7:
				// Suffle
				if (PL.first == nullptr)
					page = Page::EMPTY;
				else {
					PL.shuffle();
					current = PL.first;
					page = Page::SHUFFLE;
				}
				break;
			case 8:
				// New track
				page = Page::NEW;
				break;
			case 9:
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