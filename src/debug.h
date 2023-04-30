#ifndef DEBUG_H
#define DEBUG_H

#include "def.h"
#include "mem.h"
#include "Arr.h"
#include "Vec.h"
#include "Slice.h"

#include <stdio.h>

#define _debug(ptr, type, format) printf(format, * (type *)ptr)

static inline void debug_nl()
{
    printf("\n");
}

static inline void debug_I32(const void * ptr)
{
    _debug(ptr, I32, "%ld ");
}

static inline void debug_I64(const void * ptr)
{
    _debug(ptr, I64, "%ld ");
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

static inline void debug_Slice(const void * slice, void (* f)(const void *))
{
    Slice_apply((Slice *)slice, (void (*)(void *))f);
    // debug_nl();
    printf("\n");
}

static inline void debug_Vec(const void * vec, void (* f)(const void *))
{
    Slice slice;

    slice = Vec_to_slice(vec);
    debug_Slice(& slice, f);
}

#endif