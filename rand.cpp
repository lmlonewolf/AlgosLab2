#include "Header.h"


// Случайное число в диапазоне
int randint(int min, int max) {
    if (min == max)
        return max;
    int res = rand() % max;
    return min + rand() % (max - min + 1);
}
