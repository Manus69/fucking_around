#include "file.h"

#define NL ('\n')

static inline I64 file_size(int file)
{
    struct stat _stat;

    fstat(file, & _stat);

    return _stat.st_size;
}

Str file_to_Str(const char * filename)
{
    int file;
    Str str;
    I64 size;

    if ((file = open(filename, O_RDONLY)) < 0) return Str_empty();

    size = file_size(file);
    str = Str_zero(size);
    
    if ((read(file, Str_cstr(& str), size)) != size) return Str_empty();

    return str;
}

Vector file_to_lines(const char * filename)
{
    Str     str;
    Vector  strings;
    Slice   str_slice;
    Slice   current;

    str = file_to_Str(filename);
    str_slice = Str_to_slice(& str);
    strings = Vector_new(Str);

    while (Slice_empty(& str_slice) == false)
    {
        current = Str_split_next(& str_slice, NL);
        Vector_push(& strings, Str_from_slice(& current));
    }

    Str_destory(& str);

    return strings;
}