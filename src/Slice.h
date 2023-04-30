#ifndef SLICE_H
#define SLICE_H

#include "Sptr.h"

typedef struct Slice Slice;

struct Slice
{
    const Sptr *    sptr;
    I64             left:  INDEX_FW;
    I64             right: INDEX_FW;
};


static inline Slice Slice_sptr(const Sptr * sptr, I64 index, I64 n_items)
{
    return (Slice) {sptr, index, index + n_items};
}

static inline I64 Slice_len(const Slice * slice)
{
    return slice->right - slice->left;
}

static inline bool Slice_empty(const Slice * slice)
{
    return Slice_len(slice) <= 0;
}

static inline void Slice_shift(Slice * slice, I64 n_items)
{
    slice->left += n_items;
}

static inline void Slice_shrink(Slice * slice, I64 n_items)
{
    slice->right -= n_items;
}

static inline void * Slice_get(const Slice * slice, I64 index)
{
    return Sptr_get(slice->sptr, index + slice->left);
}

#define Slice_set(slice_ptr, index, value) (* (typeof(value) *) Slice_get((slice_ptr), (index)) = value)

static inline I64 Slice_left(const Slice * slice)
{
    return slice->left;
}

static inline I64 Slice_right(const Slice * slice)
{
    return slice->right;
}

static inline void * Slice_first(const Slice * slice)
{
    return Slice_get(slice, 0);
}

static inline void * Slice_last(const Slice * slice)
{
    return Slice_get(slice, Slice_len(slice) - 1);
}

static inline Slice Slice_slice(const Slice * slice, I64 index, I64 n_items)
{
    return Slice_sptr(slice->sptr, slice->left + index, n_items);
}

static inline Slice Slice_slice_to_end(const Slice * slice, I64 index)
{
    return Slice_sptr(slice->sptr, slice->left + index, Slice_len(slice) - index);
}

static inline void Slice_apply(Slice * slice, void (* f)(void *))
{
    mem_apply_mut(Slice_get(slice, 0), Slice_len(slice), Sptr_item_size(slice->sptr), f);
}

#endif