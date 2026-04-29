#include "Header.h"



Track::Track(std::string name, unsigned time, std::string style, unsigned short rate) : name{ name }, time{ time }, style{ style }, rate{ rate } {}

void Track::print(char type) {
	if (type == 'f')
		std::cout << '+' << std::string(32, '-') << '+' << std::string(8, '-') << '+' << std::string(16, '-') << '+' << std::string(8, '-') << '+' << std::endl;
	else if (type == 't')
		std::cout << std::format("|{:<32}|{:<8}|{:<16}|{:<8}|", name, time, style, rate) << std::endl;
}

void Track::print(void) {
	print('f');
	print('t');
	print('f');
}




Node::Node(Track& data) : data{ &data } {}
Node::Node(Track* data) : data{ data } {}



void Playlist::print() {
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


void Playlist::new_front(Track& track) {
	Node* node = new Node(track);
	size++;
	if (!first) {
		first = node;
		last = node;
		return;
	}
	node->next = first;
	first->prev = node;
	first = node;
}

void Playlist::new_last(Track& track) {
	Node* node = new Node(track);
	size++;
	if (!last) {
		first = node;
		last = node;
		return;
	}
	node->prev = last;
	last->next = node;
	last = node;
}


bool Playlist::del_track(std::string track_name) {
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

			size--;

			return true;
		}
		track = track->next;
	}
	return false;
}

bool Playlist::del_track(Track& target) {
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

			size--;

			return true;
		}
		track = track->next;
	}
	return false;
}

bool Playlist::del_track(Node& target) {
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

			size--;
			return true;
		}
		track = track->next;
	}
	return false;
}


void Playlist::shuffle(void) {
	for (int i = 0; i < size; i++) {
		Node* current = first;
		for (int j = 0; j < randint(0, size - 1 - i); j++)
			current = current->next;
		new_last(*(current->data));
		size--;
		if (current->next)
			current->next->prev = current->prev;
		if (current->prev)
			current->prev->next = current->next;
		if (current == first)
			first = current->next;

		delete current;
	}
}