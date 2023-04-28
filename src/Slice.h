#ifndef SLICE_H
#define SLICE_H

#include "Arr.h"

typedef struct Slice Slice;

struct Slice
{
    Arr * array;
    U64   left:    INDEX_FW;
    U64   right:   INDEX_FW;
};

static inline Slice Slice_Arr(const Arr * array, U64 index, U64 n_items)
{
    return (Slice) {(Arr *)array, index, index + n_items};
}

static inline U64 Slice_len(const Slice * slice)
{
    return slice->right - slice->left;
}

static inline void Slice_shift(Slice * slice, U64 n_items)
{
    slice->left += n_items;
}

static inline void Slice_shrink(Slice * slice, U64 n_items)
{
    slice->right -= n_items;
}

static inline bool Slice_empty(const Slice * slice)
{
    return slice->left == slice->right;
}

static inline void * Slice_get(const Slice * slice, U64 index)
{
    return Arr_get(slice->array, slice->left + index);
}

#define Slice_set(slice_ptr, index, value) (* (typeof(value) *)Slice_get((slice_ptr), (index)) = value)

static inline void * Slice_first(const Slice * slice)
{
    return Slice_get(slice, 0);
}

static inline void * Slice_last(const Slice * slice)
{
    return Slice_get(slice, slice->right);
}

static inline void Slice_apply(Slice * slice, void (* f)(void *))
{
    mem_apply_mut(Slice_first(slice), Slice_len(slice), Arr_item_size(slice->array), f);
}

#endif