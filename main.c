#include "debug.h"
#include "./core/def.h"
#include "./type/type.h"
#include "./structure/structure.h"
#include "./alg/sort.h"
#include "./io/file.h"

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

    I64 x = deref(I64) Array_get(& a, length - 1);
    debug_I64(& x);

    Array_destroy(& a);
}

void vector_test(I64 length)
{
    Vector v = Vector_new(I64);
    for (I64 k = 0; k < length; k ++)
    {
        Vector_push(& v, length - k);
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
#define FILE "test_file.txt"

void sort_test_str()
{
    Vector lines = file_to_lines(FILE);
    Slice slice = Vector_to_slice(& lines);

    sort(& slice, Str);

    // debug_Vector(& lines, debug_Str);
    debug_Str(Vector_last(& lines));

    Vector_wipe(& lines, (F) Str_destory);
}

void file_test()
{
    Str s = file_to_Str(FILE);

    // debug_Str(& s);

    Vector split = Str_split(& s, '\n');
    debug_Vector(& split, debug_Slice_char);

    Vector_destroy(& split);
    Str_destory(& s);
}

void bf_test()
{
    BitField f = BitField_new(3);

    debug_BitField(& f);

    BitField_destroy(& f);
}

int main()
{
    // vector_test(1 << 25);
    // sort_test(1 << 25);
    // str_test();
    // file_test();
    // sort_test_str();

    bf_test();
}