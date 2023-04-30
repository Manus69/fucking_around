#include "sort.h"
#include "debug.h"

#include <string.h>

#define QS_THRESHOLD (1 << 5)

void sort_insert(Slice * slice, Cmp cmp, Swap swap)
{
    I64 current;

    for (I64 sorted = 1; sorted < Slice_len(slice); sorted ++)
    {
        current = sorted - 1;
        while (current >= 0 && (cmp(Slice_get(slice, current), Slice_get(slice, current + 1)) > 0))
        {
            swap(Slice_get(slice, current + 1), Slice_get(slice, current));
            -- current;
        }
    }
}

static inline I64 pick_pivot_index(const Slice * slice)
{
    // return Slice_len(slice) / 2;
    return rand() % Slice_len(slice);
}

static I64 partition(Slice * slice, Cmp cmp, Swap swap)
{
    I64     pivot_index;
    void *  pivot;

    pivot_index = pick_pivot_index(slice);
    pivot = Slice_last(slice);
    swap(pivot, Slice_get(slice, pivot_index));

    pivot_index = - 1;
    for (I64 current = 0; current < Slice_len(slice); current ++)
    {
        if (cmp(Slice_get(slice, current), pivot) < 0)
        {
            pivot_index ++;
            swap(Slice_get(slice, pivot_index), Slice_get(slice, current));
        }
    }

    pivot_index ++;
    swap(Slice_get(slice, pivot_index), pivot);

    return pivot_index;
}

void sort_quick(Slice * slice, Cmp cmp, Swap swap)
{
    I64     pivot_index;
    Slice   lhs;
    Slice   rhs;
    
    if (Slice_len(slice) < QS_THRESHOLD) return sort_insert(slice, cmp, swap);

    pivot_index = partition(slice, cmp, swap);

    lhs = Slice_slice(slice, 0, pivot_index);
    rhs = Slice_slice_to_end(slice, pivot_index + 1);

    sort_quick(& lhs, cmp, swap);
    sort_quick(& rhs, cmp, swap);
}