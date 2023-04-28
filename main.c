#include "def.h"
#include "debug.h"
#include "Arr.h"
#include "Vec.h"
#include "Slice.h"

#include <stdio.h>

void array_test_U32(U32 length)
{
    Arr a = Arr_new(length, U32);
    for (U32 k = 0; k < length; k ++)
    {
        Arr_set(& a, k, length - k);
    }

    // debug_Array(& a, debug_U32);
    debug_U32(Arr_first(& a));
}

int main()
{
    U32 length = 1 << 25;

    array_test_U32(length);
}