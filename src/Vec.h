#ifndef VECTOR_H
#define VECTOR_H

#include "Sptr.h"
#include "Slice.h"

#define VEC_DEFAULT_CAPACITY    (1 << 5)

typedef struct Vec Vec;

struct Vec
{
    Sptr    sptr;
    I64     index;
};

static inline Vec Vec_allocate(I64 capacity, I64 item_size)
{
    capacity = capacity ? capacity : 1;

    return (Vec) {Sptr_allocate(capacity, item_size), 0};
}

#define Vec_new(type) Vec_allocate(VEC_DEFAULT_CAPACITY, sizeof(type))

static inline I64 Vec_len(const Vec * vec)
{
    return vec->index;
}

static inline I64 Vec_capacity(const Vec * vec)
{
    return Sptr_n_items(& vec->sptr) - Vec_len(vec);
}

static inline bool Vec_full(const Vec * vec)
{
    return Vec_capacity(vec) == 0;
}

static inline bool Vec_empty(const Vec * vec)
{
    return Vec_len(vec) == 0;
}

static inline void * Vec_get(const Vec * vec, I64 index)
{
    return Sptr_get(& vec->sptr, index);
}

static inline void * Vec_first(const Vec * vec)
{
    return Sptr_first(& vec->sptr);
}

static inline void * Vec_last(const Vec * vec)
{
    return Sptr_get(& vec->sptr, vec->index - 1);
}

#define Vec_set(vec_ptr, index, value) (* (typeof(value) *) Vec_get(vec_ptr, index) = value)

static inline void Vec_extend(Vec * vec, I64 n_items)
{
    Sptr_extend(& vec->sptr, n_items);
}

static inline void Vec_reserve(Vec * vec, I64 extra_items)
{
    if (Vec_capacity(vec) < extra_items) Vec_extend(vec, extra_items);
}

static inline void Vec_check_extend(Vec * vec)
{
    if (Vec_full(vec)) Vec_extend(vec, Vec_len(vec));
}

#define Vec_push(vec_ptr, value) \
{ \
    Vec_check_extend(vec_ptr); \
    Vec_set((vec_ptr), (vec_ptr)->index, value); \
    (vec_ptr)->index ++; \
}

static inline Slice Vec_slice(const Vec * vec, I64 index, I64 n_items)
{
    return Slice_sptr(& vec->sptr, index, n_items);
}

static inline Slice Vec_to_slice(const Vec * vec)
{
    return Vec_slice(vec, 0, Vec_len(vec));
}

static inline void Vec_destroy(Vec * vec)
{
    Sptr_destroy(& vec->sptr);
}

#endif