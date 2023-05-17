#ifndef VECTOR_H
#define VECTOR_H

#include "../core/macro.h"
#include "Array.h"
#include "Slice.h"

#define VECTOR_CAPACITY (1 << 5)

typedef struct Vector Vector;

struct Vector
{
    Array   array;
    I64     index;
};

static inline I64 Vector_len(const Vector * vector)
{
    return vector->index;
}

static inline I64 Vector_item_size(const Vector * vector)
{
    return Array_item_size(& vector->array);
}

static inline I64 Vector_capacity(const Vector * vector)
{
    return Array_len(& vector->array);
}

static inline I64 Vector_remaining_capacity(const Vector * vector)
{
    return Vector_capacity(vector) - Vector_len(vector);
}

static inline Vector Vector_new_capacity(I64 capacity, I64 item_size)
{
    return (Vector) {Array_new_size(capacity, item_size), 0};
}

#define Vector_new(type) Vector_new_capacity(VECTOR_CAPACITY, sizeof(type))

static inline void Vector_destroy(Vector * vector)
{
    Array_destroy(& vector->array);
}

static inline void * Vector_get(const Vector * vector, I64 index)
{
    return Array_get(& vector->array, index);
}

static inline void * Vector_first(const Vector * vector)
{
    return Vector_get(vector, 0);
}

static inline void * Vector_last(const Vector * vector)
{
    return Vector_get(vector, Vector_len(vector) - 1);
}

static inline void Vector_set_ptr(Vector * vector, I64 index, const void * item, Put put)
{
    Array_set_ptr(& vector->array, index, item, put);
}

#define Vector_set(vector_ptr, index, value) Array_set(& (vector_ptr)->array, (index), (value))

static inline void Vector_reserve(Vector * vector, I64 n_items)
{
    Array_extend(& vector->array, n_items);
}

static inline void Vector_check_reserve(Vector * vector)
{
    if (unlikely(Vector_remaining_capacity(vector) == 0)) Vector_reserve(vector, Vector_len(vector));
}

static inline void Vector_push_ptr(Vector * vector, const void * item, Put put)
{
    Vector_check_reserve(vector);
    Vector_set_ptr(vector, vector->index, item, put);
    vector->index ++;
}

#define Vector_push(vector_ptr, value) \
{ \
    Vector_check_reserve(vector_ptr); \
    Vector_set((vector_ptr), (vector_ptr)->index, (value)); \
    (vector_ptr)->index ++; \
}

static inline Slice Vector_slice(const Vector * vector, I64 start, I64 length)
{
    return Slice_new(Vector_get(vector, start), length, Vector_item_size(vector));
}

static inline Slice Vector_to_slice(const Vector * vector)
{
    return Vector_slice(vector, 0, Vector_len(vector));
}

static inline void Vector_apply(Vector * vector, F f)
{
    Slice slice;

    slice = Vector_to_slice(vector);

    return Slice_apply(& slice, f);
}

static inline void Vector_destroy_items(Vector * vector, F f)
{
    Vector_apply(vector, f);
}

static inline void Vector_wipe(Vector * vector, F f)
{
    Vector_destroy_items(vector, f);
    Vector_destroy(vector);
}

#endif