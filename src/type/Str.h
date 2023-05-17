#ifndef STR_H
#define STR_H

#include "../structure/Block.h"
#include "../structure/Slice.h"
#include "../structure/Vector.h"
#include "../core/macro.h"
#include <string.h>

typedef Block Str;

mem_put_gen(Str)
mem_swap_gen(Str)

static inline I64 Str_len(const Str * str)
{
    return Block_size(str) - 1;
}

static inline Str Str_new(const char * cstr)
{
    return Block_from_ptr(cstr, strlen(cstr) + 1);
}

static inline Str Str_zero(I64 length)
{
    return Block_zero(length + 1);
}

static inline Str Str_empty(void)
{
    return Str_zero(0);
}

static inline void Str_destory(Str * str)
{
    Block_destroy(str);
}

static inline char * Str_cstr(const Str * str)
{
    return (char *) Block_data(str);
}

static inline I64 Str_cmp(const void * lhs, const void * rhs)
{
    // return strcmp(Str_cstr((const Str *)lhs), Str_cstr((const Str *)rhs));
    I64 length;

    length = min(Str_len((const Str *)lhs), Str_len((const Str *)rhs));

    return strncmp(Str_cstr((const Str *)lhs), Str_cstr((const Str *)rhs), length + 1);
}

static inline void * Str_get(const Str * str, I64 index)
{
    return Block_get(str, index);
}

static inline char Str_at(const Str * str, I64 index)
{
    return deref(char) Str_get(str, index);
}

static inline Slice Str_slice(const Str * str, I64 index, I64 length)
{
    return Slice_new(Str_get(str, index), length, sizeof(char));
}

static inline Slice Str_to_slice(const Str * str)
{
    return Str_slice(str, 0, Str_len(str));
}

Slice_find_gen(char)

static inline I64 Str_find_c(const Str * str, char c)
{
    Slice slice;

    slice = Str_to_slice(str);

    return Slice_find_char(& slice, c);
}

Slice   Str_split_next(Slice * str_slice, char c);
Vector  Str_split(const Str * str, char c);

#endif