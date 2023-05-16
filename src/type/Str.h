#ifndef STR_H
#define STR_H

#include "../structure/Block.h"
#include "../core/macro.h"
#include <string.h>

typedef Block Str;

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

#endif