#include "def.h"
#include "debug.h"
#include "Arr.h"
#include "Vec.h"
#include "Slice.h"
#include "sort.h"

#include <stdio.h>

static inline I64 cmp_I64(const void * lhs, const void * rhs)
{
    return * (I64 *) lhs - * (I64 *) rhs;
}

void vec_int_test(I64 length)
{
    Vec v = Vec_new(I64);


    for (I64 k = 0; k < length; k ++)
    {
        Vec_push(& v, length - k);
    }

    // debug_Vec(& v, debug_I64);

    Slice s = Vec_to_slice(& v);
    sort_quick(& s, cmp_I64, swap_I64);
    // sort_insert(& s, cmp_I64, swap_I64);

    debug_I64(Vec_last(& v));
    // debug_Vec(& v, debug_I64);

    Vec_destroy(& v);
}
int main()
{
    I64 length = 1 << 20;


    vec_int_test(length);
}