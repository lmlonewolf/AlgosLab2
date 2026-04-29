#include "Header.h"
#include <utility>

int select = 0;


int main() {
	srand(time(0));
	Track t1 = Track("hello", 1, "pop", 5);
	Track t2 = Track("world", 2, "kpop", 4);
	Track t3 = Track("mix", 3, "rock", 10);

	Playlist p;
	p.new_last(t1);
	p.new_last(t2);
	p.new_last(t3);

	menu_selector(p);


	return 0;
}