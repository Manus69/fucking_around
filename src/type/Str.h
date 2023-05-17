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

static inline Str Str_buffer(I64 length)
{
    Block block;

    block = Block_new(length + 1);
    Block_set(& block, length, (char) 0);

    return block;
}

static inline Str Str_from_slice(const Slice * slice)
{
    Str str;
    I64 length;

    length = Slice_len(slice);
    str = Str_buffer(length);
    memcpy(Block_data(& str), Slice_first(slice), length);

    return str;
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
    return strcmp(Str_cstr((const Str *)lhs), Str_cstr((const Str *)rhs));
}

static inline void * Str_get(const Str * str, I64 index)
{
    return Block_get(str, index);
}

static inline char Str_at(const Str * str, I64 index)
{
    return deref(char) Str_get(str, index);
}

static inline void Str_set(Str * str, I64 index, char c)
{
    deref (char) Str_get(str, index) = c;
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

static inline void Str_append_cstr_len(Str * str, const char * cstr, I64 length)
{
    Block_extend(str, length);
    memcpy(str->data + Str_len(str), cstr, length);
    str->size += length;
    Str_set(str, Str_len(str), 0);
}

static inline void Str_append_cstr(Str * str, const char * cstr)
{
    return Str_append_cstr_len(str, cstr, strlen(cstr));
}

static inline void Str_append(Str * lhs, const Str * rhs)
{
    return Str_append_cstr_len(lhs, Str_cstr(rhs), Str_len(rhs));
}

Slice   Str_split_next(Slice * str_slice, char c);
Vector  Str_split(const Str * str, char c);

#endif