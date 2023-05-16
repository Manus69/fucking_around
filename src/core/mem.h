#ifndef MEM_H
#define MEM_H

#include "def.h"

#include <assert.h>

void mem_vapply(void (*f)(void *), ...);

static inline void * mem_point(const void * ptr, I64 index, I64 item_size)
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
static inline void type##_swap(void * lhs, void * rhs) \
{ mem_swap((type *)lhs, (type *)rhs); }

#define mem_put_gen(type) \
static inline void type##_put(void * target, const void * src) \
{ deref(type) target = deref(type) src; }


static inline void * mem_allocate(I64 size)
{
    void * ptr;

    if ((ptr = malloc(size))) return ptr;

    assert(0);
    return NULL;
}

static inline void * mem_zero(I64 size)
{
    void * ptr;

    if ((ptr = calloc(size, 1))) return ptr;

    assert(0);
    return NULL;
}

static inline void mem_destroy(void * ptr)
{
    free(ptr);
}

static inline void * mem_reallocate(void * ptr, I64 size)
{
    void * new_ptr;

    if ((new_ptr = realloc(ptr, size))) return new_ptr;

    assert(0);
    return NULL;
}

static inline void * mem_extend(void * ptr, I64 current_size, I64 extra_size)
{
    return mem_reallocate(ptr, current_size + extra_size);
}

static inline void mem_apply_mut(void * data, I64 n_items, I64 item_size, void (* f)(void *))
{
    while (n_items --)
    {
        f(data);
        data += item_size;
    }
}

static inline void mem_apply(const void * data, I64 n_items, I64 item_size, void (* f)(const void *))
{
    mem_apply_mut((void *)data, n_items, item_size, (void (*)(void *))f);
}

#endif