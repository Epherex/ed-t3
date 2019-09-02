#ifndef HEAPSORT_H
#define HEAPSORT_H

#include <stdbool.h>

typedef void *Item;

void heapsort(Item *a, int n, int ate, int (*cmp)(const void*, const void*));

#endif