#include "U8.h"
#include "../type/Str.h"

static char values[] = {'0', '1'};

Str U8_to_Str(const U8 * byte)
{
    char    buffer[BPB + 1] = {0};
    U8      value;
    U64     index;

    index = 0;
    value = * byte;
    while (index < BPB)
    {
        deref(U8) (buffer + index) = values[value & 1];
        index ++;
        value >>= 1;
    }

    return Str_new(buffer);
}