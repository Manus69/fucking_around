#ifndef SPTR_H
#define SPTR_H

#include "def.h"
#include "mem.h"

typedef struct Sptr Sptr;

struct Sptr
{
    void *  ptr;
    I64     n_items:    INDEX_FW;
    I64     item_size:  INDEX_FW;
};

static inline Sptr Sptr_allocate(I64 n_items, I64 item_size)
{
    return (Sptr) {mem_allocate(n_items * item_size), n_items, item_size};
}

#define Sptr_new(n_items, type) Sptr_allocate(n_items, sizeof(type))

static inline void * Sptr_get(const Sptr * sptr, I64 index)
{
    return mem_point(sptr->ptr, index, sptr->item_size);
}

#define Sptr_set(sptr_ptr, index, value) (* (typeof(value) *) Sptr_get((sptr_ptr), (index)) = value)

static inline I64 Sptr_n_items(const Sptr * sptr)
{
    return sptr->n_items;
}

static inline I64 Sptr_size(const Sptr * sptr)
{
    return sptr->n_items * sptr->item_size;
}

static inline I64 Sptr_item_size(const Sptr * sptr)
{
    return sptr->item_size;
}

static inline void * Sptr_first(const Sptr * sptr)
{
    return sptr->ptr;
}

static inline void * Sptr_last(const Sptr * sptr)
{
    return Sptr_get(sptr, Sptr_n_items(sptr) - 1);
}

static inline void Sptr_apply(Sptr * sptr, void (* f)(void *))
{
    mem_apply_mut(sptr->ptr, sptr->n_items, sptr->item_size, f);
}

static inline void Sptr_destroy_items(Sptr * sptr, void (* f)(void *))
{
    Sptr_apply(sptr, f);
}

static inline void Sptr_destroy(Sptr * sptr)
{
    mem_destroy(sptr->ptr);
}

static inline void Sptr_extend(Sptr * sptr, I64 n_items)
{
    sptr->ptr = mem_extend(sptr->ptr, Sptr_size(sptr), n_items * sptr->item_size);
    sptr->n_items += n_items;
}

#endif