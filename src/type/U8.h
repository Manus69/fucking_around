#ifndef U8_H
#define U8_H

#include "../core/mem.h"
#include "../type/Str.h"

mem_put_gen(U8)
mem_swap_gen(U8)

Str U8_to_Str(const U8 * byte);

#endif