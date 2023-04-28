#ifndef DEBUG_H
#define DEBUG_H

#include "def.h"
#include "mem.h"
#include "Arr.h"

#include <stdio.h>

#define _debug(ptr, type, format) printf(format, * (type *)ptr)

static inline void debug_I32(const void * ptr)
{
    _debug(ptr, I32, "%ld ");
}

static inline void debug_U32(const void * ptr)
{
    _debug(ptr, U32, "%lu ");
}

static inline void debug_cstr(const void * cstr)
{
    _debug(cstr, char *, "%s ");
}

#define debug_mem(ptr, n_items, f, type) mem_apply(ptr, n_items, sizeof(type), f)

static inline void debug_Array(const void * array, void (* f)(const void *))
{
    mem_apply(Arr_get(array, 0), Arr_len(array), Arr_item_size(array), f);
}

#endif