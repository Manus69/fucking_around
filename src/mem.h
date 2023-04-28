#ifndef MEM_H
#define MEM_H

#include "def.h"

static inline void * mem_point(const void * ptr, U64 index, U64 item_size)
{
    return (void *)(ptr + (index * item_size));
}

#define mem_swap(lhs, rhs) \
{ \
    typeof(* (lhs)) _t = * (lhs); \
    * (lhs) = * (rhs); \
    * (rhs) = _t; \
} \

#define mem_swap_gen(type) \
static inline void swap_##type(void * lhs, void * rhs) \
{ mem_swap((type *)lhs, (type *)rhs); }

#define mem_set_gen(type) \
static inline void set_##type(void * target, U64 index, const void * src) \
{ ((type *)target)[index] = * (type *)src; }

mem_set_gen(Ptr)
mem_swap_gen(Ptr)

static inline void * mem_allocate(U64 size)
{
    void * ptr;

    if ((ptr = malloc(size))) return ptr;

    exit(NOT_OK);
}

static inline void mem_destroy(void * ptr)
{
    free(ptr);
}

static inline void * mem_reallocate(void * ptr, U64 size)
{
    void * new_ptr;

    if ((new_ptr = realloc(ptr, size))) return new_ptr;

    exit(NOT_OK);
}

static inline void * mem_extend(void * ptr, U64 current_size, U64 extra_size)
{
    return mem_reallocate(ptr, current_size + extra_size);
}

static inline void mem_apply_mut(void * data, U64 n_items, U64 item_size, void (* f)(void *))
{
    while (n_items --)
    {
        f(data);
        data += item_size;
    }
}

static inline void mem_apply(const void * data, U64 n_items, U64 item_size, void (* f)(const void *))
{
    mem_apply_mut((void *)data, n_items, item_size, (void (*)(void *))f);
}

#endif