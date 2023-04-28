#ifndef VECTOR_H
#define VECTOR_H

#include "Arr.h"

#define VEC_DEFAULT_CAPACITY    (1 << 5)

typedef struct Vec Vec;

struct Vec
{
    Arr array;
    U64 index: INDEX_FW;
};

#endif