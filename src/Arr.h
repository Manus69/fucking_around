#ifndef ARR_H
#define ARR_H

#include "def.h"
#include "mem.h"

typedef struct Arr Arr;

struct Arr
{
    void *  data;
    U64     length:     INDEX_FW;
    U64     item_size:  INDEX_FW;
};

static inline Arr Arr_create(U64 length, U64 item_size)
{
    return (Arr) {mem_allocate(length * item_size), length, item_size}; 
}

#define Arr_new(length, type) Arr_create(length, sizeof(type));

static inline U64 Arr_len(const Arr * array)
{
    return array->length;
}

static inline void * Arr_get(const Arr * array, U64 index)
{
    return mem_point(array->data, index, array->item_size);
}

static inline void * Arr_first(const Arr * array)
{
    return Arr_get(array, 0);
}

static inline void * Arr_last(const Arr * array)
{
    return Arr_get(array, Arr_len(array) - 1);
}

#define Arr_set(arr_ptr, index, value) (* (typeof(value) *)Arr_get((arr_ptr), (index)) = value)

static inline U64 Arr_item_size(const Arr * array)
{
    return array->item_size;
}

static inline U64 Arr_data_size(const Arr * array)
{
    return array->length * array->item_size;
}

static inline void Arr_destroy_data(Arr * array)
{
    mem_destroy(array->data);
}

static inline void Arr_extend(Arr * array, U64 n_items)
{
    array->data = mem_extend(array->data, Arr_data_size(array), Arr_item_size(array) * n_items);
    array->length += n_items;
}

#endif