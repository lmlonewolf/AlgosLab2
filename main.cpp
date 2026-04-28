#include "Header.h"

int select = 0;

struct Track {
	std::string name;
	unsigned time;
	std::string style;
	unsigned short rate;
	Track* prev = nullptr;
	Track* next = nullptr;

	Track(std::string name, unsigned time, std::string style, unsigned short rate) : name {name}, time {time}, style {style}, rate {rate} {}

	void print(char type) {
		if (type == 'f')
			std::cout << '+' << std::string(32, '-') << '+' << std::string(8, '-') << '+' << std::string(16, '-') << '+' << std::string(8, '-') << '+' << std::endl;
		else if (type == 't')
			std::cout << std::format("|{:<32}|{:<8}|{:<16}|{:<8}|", name, time, style, rate) << std::endl;
	}
	void print(void) {
		print('f');
		print('t');
		print('f');
	}

};


class Playlist {
	Track* first = nullptr;
	Track* last = nullptr;
	bool repeat = false;

public:
	void print() {
		Track* track = first;
		std::cout << std::endl;
		while (track != nullptr) {
			track->print('f');
			track->print('t');
			track = track->next;
		}
		track->print('f');
	}

	void new_front(Track& track) {
		if (!first) {
			first = &track;
			last = &track;
			return;
		}
			track.next = first;
			first->prev = &track;
			first = &track;
	}

	void new_last(Track& track) {
		if (!last) {
			first = &track;
			last = &track;
			return;
		}
		track.prev = last;
		last->next = &track;
		last = &track;
	}

	bool del_track(std::string track_name) {
		Track* track = first;

		while (track != nullptr) {
			if (track->name == track_name) {

				if (track->prev)
				track->prev->next = track->next;
				if (track->next)
					track->next->prev = track->prev;
				if (track == first)
					first = track->next;
				if (track == last)
					last = track->prev;

				track->next = nullptr;
				track->prev = nullptr;

				return true;
			}
			track = track->next;
		}
		return false;
	}

	bool del_track(Track& target) {
		Track* track = first;

		while (track != nullptr) {
			if (track == &target) {

				if (track->prev)
					track->prev->next = track->next;
				if (track->next)
					track->next->prev = track->prev;
				if (track == first)
					first = track->next;
				if (track == last)
					last = track->prev;

				track->next = nullptr;
				track->prev = nullptr;

				return true;
			}
			track = track->next;
		}
		return false;
	}
};

int main() {
	srand(time(0));
	Track t1 = Track("hello", 1, "pop", 5);
	Track t2 = Track("world", 2, "kpop", 4);
	Track t3 = Track("mix", 3, "rock", 10);

	Playlist p;
	p.new_last(t1);
	p.new_last(t2);
	p.new_last(t3);


	p.print();

	return 0;
}