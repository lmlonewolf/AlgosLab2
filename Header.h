#pragma once

#include <iostream>
#include <string>
#include <format>


struct Track {
	std::string name;
	unsigned time;
	std::string style;
	unsigned short rate;

	Track(void);
	Track(std::string name, unsigned time, std::string style, unsigned short rate);

	void print(char type);
	void print(void);
};


struct Node {
	Track* data;
	Node* prev = nullptr;
	Node* next = nullptr;

	Node(void);
	Node(Track* data);
};


class Playlist {
	size_t size = 0;
	size_t sum_time = 0;
	size_t sum_rate = 0;
public:
	Node* first = nullptr;
	Node* last = nullptr;
	bool repeat_pl = false;
	bool repeat_tr = false;


	void print(void);

	size_t get_size(void);

	void new_front(Track* track);

	void new_last(Track* track);

	bool del_track(std::string track_name);

	bool del_track(Track& target);

	bool del_track(Node& target);

	bool del_track(size_t number);

	void shuffle(void);
};


void menu_selector(Playlist& PL);

int move(size_t& select, size_t size);

int randint(int min, int max);




void track_selector(Playlist& PL);