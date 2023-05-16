#ifndef SLICE_H
#define SLICE_H

#include "../core/def.h"
#include "../core/macro.h"

typedef struct Slice Slice;

struct Slice
{
    void *  start;
    void *  end;
    I64     item_size;
};

static inline Slice Slice_new(const void * data, I64 length, I64 item_size)
{
    return (Slice) {(void *)data, (void *)data + length * item_size, item_size};
}

static inline I64 Slice_size(const Slice * slice)
{
    return slice->end - slice->start;
}

static inline I64 Slice_len(const Slice * slice)
{
    return Slice_size(slice) / slice->item_size;
}

static inline bool Slice_empty(const Slice * slice)
{
    return Slice_size(slice) == 0;
}

static inline void * Slice_get(const Slice * slice, I64 index)
{
    return slice->start + index * slice->item_size;
}

static inline void Slice_set_ptr(Slice * slice, I64 index, const void * item, Put put)
{
    put(Slice_get(slice, index), item);
}

#define Slice_set(slice_ptr, index, value) \
(deref(typeof(value)) Slice_get((slice_ptr), (index)) = value)

static inline void Slice_shift(Slice * slice, I64 n_items)
{
    slice->start += n_items * slice->item_size;
}

static inline void Slice_shrink(Slice * slice, I64 n_items)
{
    slice->end -= n_items * slice->item_size;
}

#endif