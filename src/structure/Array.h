#ifndef ARRAY_H
#define ARRAY_H

#include "Block.h"

typedef struct Array Array;

struct Array
{
    Block   block;
    I64     item_size;
};

static inline I64 Array_len(const Array * array)
{
    return Block_size(& array->block) / array->item_size;
}

static inline I64 Array_size(const Array * array)
{
    return Block_size(& array->block);
}

static inline Array Array_new_size(I64 length, I64 item_size)
{
    return (Array) {Block_new(length * item_size), item_size};
}

#define Array_new(length, type) Array_new_size(length, sizeof(type))

static inline void Array_destroy(Array * array)
{
    Block_destroy(& array->block);
}

static inline void * Array_get(const Array * array, I64 index)
{
    return Block_get(& array->block, index * array->item_size);
}

static inline void Array_set_ptr(Array * array, I64 index, const void * item, Put put)
{
    put(Array_get(array, index), item);
}

#define Array_set(array_ptr, index, value) \
Block_set(& (array_ptr)->block, (index) * (array_ptr)->item_size, (value))

static inline void Array_extend(Array * array, I64 n_items)
{
    Block_extend(& array->block, n_items * array->item_size);
}

#endif