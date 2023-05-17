#include "Str.h"

Slice Str_split_next(Slice * str_slice, char c)
{
    I64 index;

    index = Slice_find_char(str_slice, c);

    if (unlikely(index == NO_INDEX)) return Slice_chop_to_end(str_slice, 0);

    return Slice_chop(str_slice, 0, index + 1);
}

Vector Str_split(const Str * str, char c)
{
    Vector  slices;
    Slice   str_slice;
    Slice   current;

    slices = Vector_new(Slice);
    str_slice = Str_to_slice(str);

    while (Slice_empty(& str_slice) == false)
    {
        current = Str_split_next(& str_slice, c);
        Vector_push(& slices, current);
    }

    return slices;
}