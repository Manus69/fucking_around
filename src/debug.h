#ifndef DEBUG_H
#define DEBUG_H

#include "./core/mem.h"
#include "./core/def.h"
#include "./structure/Slice.h"

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
    Slice_apply((Slice *)slice, (F) f);
    debug_nl();
}

#endif