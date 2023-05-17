#include "BitField.h"
#include "../type/Str.h"

Str BitField_to_Str(const BitField * field)
{
    Str str;

    str = Str_empty();
    for (I64 index = 0; index < field->n_bytes; index ++)
    {
        Str_append_cstr_len(& str, (char *) & field->bytes[index], BPB);
    }

    return str;
}