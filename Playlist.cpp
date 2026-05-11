#include "Header.h"
#include <sstream>

Track::Track(void) {};
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


Node::Node(void) {
	this->data = new Track();
}
Node::Node(Track* data) : data{ data } {}


void Playlist::clear(void) {
	Node* current = first;
	Node* next = nullptr;
	for (int j = 0; j < size; j++) {
		next = current->next;
		delete current;
		current = next;
	}
}


void Playlist::print() {
	Node* track = first;
	if (!track) {
		track = new Node();
		std::cout << std::endl;
		track->data->print('f');
		std::cout << std::format("|{:<32}|{:<8}|{:<16}|{:<8}|", "Name", "Time", "Style", "Rating") << std::endl;
		track->data->print('f');
		delete track->data;
		delete track;
		return;
	}
	std::cout << std::endl;
	track->data->print('f');
	std::cout << std::format("|{:<32}|{:<8}|{:<16}|{:<8}|", "Name", "Time", "Style", "Rating") << std::endl;
	while (track->next) {
		track->data->print('f');
		track->data->print('t');
		track = track->next;
	}
	track->data->print();
}

size_t Playlist::get_size(void) {
	return this->size;
}


void Playlist::new_front(Track* track) {
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
	sum_time += track->time;
	sum_rate += track->rate;
}

void Playlist::new_last(Track* track) {
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
	sum_time += track->time;
	sum_rate += track->rate;
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
			sum_time -= track->data->time;
			sum_rate -= track->data->rate;
			return true;
		}
		track = track->next;
	}
	return false;
}

bool Playlist::del_track(size_t number) {
	if (number >= size)
		return false;
	Node* track = first;
	for (int j = 0; j < number; j++)
		track = track->next;

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
	sum_time -= track->data->time;
	sum_rate -= track->data->rate;
	return true;
}

void Playlist::shuffle(void) {
	for (int i = 0; i < size; i++) {
		Node* current = first;
		for (int j = 0; j < randint(0, size - 1 - i); j++)
			current = current->next;
		new_last(current->data);
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

std::tuple <int, int> Playlist::report(void) {
	return std::make_tuple(sum_time, sum_rate / static_cast<int> (size));
}

void Playlist::save_to_file() {
	std::ofstream out("data.b");
	if (!out) return;

	Node* current = first;
	while (current) {

		std::string raw = current->data->name + "|" +
			std::to_string(current->data->time) + "|" +
			current->data->style + "|" +
			std::to_string(current->data->rate);

		out << base64_encode(raw) << "\n";
		current = current->next;
	}
	out.close();
}

void Playlist::load_from_file() {
	std::ifstream in("data.b");
	if (!in) return;

	std::string b64line;
	while (std::getline(in, b64line)) {
		if (b64line.empty()) continue;

		std::string raw = base64_decode(b64line);

		std::stringstream ss(raw);
		std::string name, style, t_time, t_rate;

		std::getline(ss, name, '|');
		std::getline(ss, t_time, '|');
		std::getline(ss, style, '|');
		std::getline(ss, t_rate, '|');

		if (!name.empty()) {
			this->new_last(new Track(name, std::stoul(t_time), style, (unsigned short)std::stoi(t_rate)));
		}
	}
	in.close();
}
