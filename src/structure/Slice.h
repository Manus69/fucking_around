#ifndef SLICE_H
#define SLICE_H

#include "../core/def.h"
#include "../core/macro.h"
#include "../core/mem.h"

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

static inline Slice Slice_slice(const Slice * slice, I64 index, I64 length)
{
    return Slice_new(slice->start + index * slice->item_size, length, slice->item_size);
}

static inline Slice Slice_slice_to_end(const Slice * slice, I64 index)
{
    return Slice_slice(slice, index, Slice_len(slice) - index);
}

static inline Slice Slice_chop(Slice * slice, I64 index, I64 length)
{
    Slice new_slice;

    new_slice = Slice_slice(slice, index, length);
    Slice_shift(slice, length);

    return new_slice;
}

static inline Slice Slice_chop_to_end(Slice * slice, I64 index)
{
    return Slice_chop(slice, index, Slice_len(slice));
}

static inline void Slice_apply(Slice * slice, F f)
{
    mem_apply_mut(slice->start, Slice_len(slice), slice->item_size, f);
}

static inline void * Slice_first(const Slice * slice)
{
    return slice->start;
}

static inline void * Slice_last(const Slice * slice)
{
    return Slice_get(slice, Slice_len(slice) - 1);
}

#endif