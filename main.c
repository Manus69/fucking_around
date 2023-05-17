#include "debug.h"
#include "./core/def.h"
#include "./type/I64.h"
#include "./structure/Block.h"
#include "./structure/Array.h"
#include "./structure/Vector.h"
#include "./structure/Slice.h"
#include "./type/Str.h"
#include "./alg/sort.h"

#include <stdio.h>
#include <assert.h>

void str_test()
{
    Str s = Str_new("eat a bag of dicks!\n");

    Vector v = Str_split(& s, ' ');

    debug_Vector(& v, debug_Slice_char);

    Vector_destroy(& v);
    Str_destory(& s);
}

void array_test(I64 length)
{
    Array a = Array_new(length, I64);

    for (I64 k = 0; k < length; k ++)
    {
        Array_set(& a, k, length - k);
    }

    I64 x = * (I64 *) Array_get(& a, length - 1);
    debug_I64(& x);

    Array_destroy(& a);
}

void vector_test(I64 length)
{
    Vector v = Vector_new(I64);
    for (I64 k = 0; k < length; k ++)
    {
        Vector_push(& v, length - k);
        // I64 x = length - k;
        // Vector_push_ptr(& v, & x, set_I64);
    }

    I64 x = deref(I64) Vector_get(& v, length - 1);
    debug_I64(& x);

    Slice s = Vector_slice(& v, 1, 10);
    debug_Slice(& s, debug_I64);

    Vector_destroy(& v);
}

void sort_test(I64 length)
{
    Vector v = Vector_new(I64);

    for (I64 k = 0; k < length; k ++)
    {
        Vector_push(& v, length - k);
    }

    Slice s = Vector_to_slice(& v);
    sort(& s, I64);
    // debug_Slice(& s, debug_I64);
    debug_I64(Slice_last(& s));

    Vector_destroy(& v);
}

struct t {int x; float y;};

int main()
{
    // vector_test(1 << 25);
    // sort_test(1 << 25);

    str_test();
}