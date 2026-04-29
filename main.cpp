#include "Header.h"

int select = 0;


struct Track {
	std::string name;
	unsigned time;
	std::string style;
	unsigned short rate;

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


struct Node {
	Track* data;
	Node* prev = nullptr;
	Node* next = nullptr;

	Node(Track& data) : data {&data} {}
	Node(Track* data) : data {data} {}
};


class Playlist {
	Node* first = nullptr;
	Node* last = nullptr;
	size_t size = 0;
	bool repeat = false;

public:

	void print() {
		Node* track = first;
		std::cout << std::endl;
		while (track->next) {
			track->data->print('f');
			track->data->print('t');
			track = track->next;
		}
		track->data->print('f');
		track->data->print('t');
		track->data->print('f');
	}


	void new_front(Node& node) {
		size++;
		if (!first) {
			first = &node;
			last = &node;
			return;
		}
			node.next = first;
			first->prev = &node;
			first = &node;
	}

	void new_front(Track& track) {
		Node* node = new Node(track);
		new_front(*node);
	}


	void new_last(Node& node) {
		size++;
		if (!last) {
			first = &node;
			last = &node;
			return;
		}
		node.prev = last;
		last->next = &node;
		last = &node;
	}

	void new_last(Track& track) {
		Node* node = new Node(track);
		new_last(*node);
	}


	bool del_track(std::string track_name) {
		Node* track = first;

		while (track != nullptr) {
			if (track->data->name == track_name) {

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

				delete track;
				size--;
				
				return true;
			}
			track = track->next;
		}
		return false;
	}

	bool del_track(Track& target) {
		Node* track = first;

		while (track != nullptr) {
			if (track->data == &target) {

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

				delete track;
				size--;

				return true;
			}
			track = track->next;
		}
		return false;
	}

	bool del_track(Node& target) {
		Node* track = first;

		while (track != nullptr) {
			if (track->data == target.data) {

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

				delete track;
				size--;

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

	p.del_track(t2);

	p.print();

	menu_selector();

	return 0;
}