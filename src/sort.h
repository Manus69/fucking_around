#ifndef SORT_H
#define SORT_H

#include "Slice.h"

void sort_insert(Slice * slice, Cmp cmp, Swap swap);
void sort_quick(Slice * slice, Cmp cmp, Swap swap);
void sort_merge(Slice * slice, Cmp cmp, Set set);

#endif