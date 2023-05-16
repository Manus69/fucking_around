#ifndef SORT_H
#define SORT_H

#include "../core/def.h"
#include "../structure/Slice.h"

void sort_quick(Slice * slice, Cmp cmp, Put put, Swap swap);
void sort_insert(Slice * slice, Cmp cmp, Put put, Swap swap);

#define sort(slice_ptr, type) (sort_quick(slice_ptr, type##_cmp, type##_put, type##_swap))

#endif