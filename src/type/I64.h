#ifndef I64_H
#define I64_H

#include "../core/mem.h"

mem_set_gen(I64)
mem_swap_gen(I64)

static inline I64 I64_cmp(const void * lhs, const void * rhs)
{
    return * (I64 *) lhs - * (I64 *) rhs;
}

#endif