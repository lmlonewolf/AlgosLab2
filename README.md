# Лабораторная работа 2
# Музыкальный плейлист (Playlist)
---

# Выбраная структура и реализация
## Для создания плейлиста было принято решение использлвать *Двусвязный список*

## Структура данных
``` cpp
struct Track {
	std::string name; // Название трека
	unsigned time; // Длительность в секундах
	std::string style; // Жанр
	unsigned short rate; // Рейтин
}
```

## Узлы
``` cpp
struct Node {
	Track* data; // Указатель на данные
	Node* prev = nullptr; // Указатель на предыдущий узел
	Node* next = nullptr; // Указатель на следующий узел
}
```
## Плейлист
``` cpp
class Playlist {
	size_t size = 0; // Количество треков
	size_t sum_time = 0; // Суммарная длительность плейлста
	size_t sum_rate = 0; // Суммарный рейтинг
public:
	Node* first = nullptr; // Указатель на первый узел
	Node* last = nullptr; // Указатель на последний узел
	bool repeat_pl = false; // Флаг состояния повтора плейлиста
	bool repeat_tr = false; // Флаг состояния повтора трека
}
```
---
# Реализованный функционал

## Обязательная часть

### Добавление трека в начало
``` cpp
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
```
### Добавление трека в конец
``` cpp
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
```

### Удаление трека (создано 2 перегрузки для разных ситуаций)
### Первая - по ссылке
``` cpp
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
```
### Вторая - по номеру
``` cpp
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
```

### Перемешивание
``` cpp
void Playlist::shuffle(void) {
	for (int i = 0; i < size; i++) {
		Node* current = first;
		for (int j = 0; j < randint(0, size - 1 - i); j++) // randint(n, m) - функция возвращающая случайное число от n до m, реализовага отдельно
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
```

### Повтор реализован в интерфейсе (то есть описывает условия перехода к другим трекам)
### Повтор плейлиста
``` cpp
if (PL.first == nullptr) // PL - плейлист
				page = Page::EMPTY;
else {
				PL.repeat_pl = !PL.repeat_pl;
				PL.repeat_tr = false;
				page = Page::REP_PL;
}
```
### Повтор трека
``` cpp
if (PL.first == nullptr) // PL - плейлист
				page = Page::EMPTY;
else {
				PL.repeat_tr = !PL.repeat_tr;
				PL.repeat_pl = false;
				page = Page::REP_TR;
}
```


