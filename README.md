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
---
## Вариативный ункционал

### Сохранение плейлиста в текстовый файл
``` cpp
static const std::string b64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string base64_encode(const std::string& in) {
    std::string out;
    int val = 0, valb = -6;
    for (unsigned char c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back(b64chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }
    if (valb > -6) out.push_back(b64chars[((val << 8) >> (valb + 8)) & 0x3F]);
    while (out.size() % 4) out.push_back('=');
    return out;
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

```




### Загрузка плейлиста из Base64-файла
``` cpp
static const std::string b64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

std::string base64_decode(const std::string& in) {
    std::string out;
    std::vector<int> T(256, -1);
    for (int i = 0; i < 64; i++) T[b64chars[i]] = i;
    int val = 0, valb = -8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val >> valb) & 0xFF));
            valb -= 8;
        }
    }
    return out;
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

```

### Вывод плейлиста в виде таблицы с выравниванием колонок
``` cpp
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
```
### Пример
```
+--------------------------------+--------+----------------+--------+
|Name                            |Time    |Style           |Rating  |
+--------------------------------+--------+----------------+--------+
|hello world                     |120     |jazz            |10      |
+--------------------------------+--------+----------------+--------+
|Stanciya Tuman                  |237     |Rock            |100     |
+--------------------------------+--------+----------------+--------+
```

### Формирование отчета (общая длительность, средний рейтинг)
``` cpp
std::tuple <int, int> Playlist::report(void) {
	return std::make_tuple(sum_time, sum_rate / static_cast<int> (size));
}
```

### Поиск N треков в заданном диапазоне времени

