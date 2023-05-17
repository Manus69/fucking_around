#ifndef TABLE_H
#define TABLE_H

#include "Array.h"
#include "Vector.h"

typedef struct Table Table;

struct Table
{
    Array array;
};

static inline Table Table_new_capacity(I64 desired_capacity, I64 item_size)
{
    return (Table) {Array_zero((U64)1 << (log2(desired_capacity) + 1), item_size)};
}

static inline I64 Table_capacity(const Table * table)
{
    return Array_len(& table->array);
}





#endif