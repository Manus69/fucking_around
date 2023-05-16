#include "mem.h"
#include <stdarg.h>

void mem_vapply(void (*f)(void *), ...)
{
    va_list args;
    void *  current;

    va_start(args, f);

    while ((current = va_arg(args, void *)))
    {
        f(current);
    }

    va_end(args);
}