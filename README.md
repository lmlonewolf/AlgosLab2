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
